/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: May 08,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "io.hpp"

#include <sstream>
#include "../common/file.hpp"
#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

std::vector<string> get_column_list(const fio_reader &reader)
{
    std::vector<string> column_names;
#ifdef NOFOREACH
    BOOST_FOREACH(auto c, reader)
#else
    for(auto c: reader)
#endif
        column_names.push_back(c.name());

    return column_names;
}

//-----------------------------------------------------------------------------
operation::array_type read_column(const string &cname,fio_reader &reader)
{
    operation::array_type data;
    try
    {
        data = operation::array_type(operation::shape_type{reader.nrecords()},
                        reader.column<operation::array_type::storage_type>(cname));
    }
    catch(key_error &error)
    {
        std::stringstream ss;
        ss<<"Error reading column ["<<cname<<"] - column does not exist!"<<std::endl;
        ss<<"The following columns are available in this file:"<<std::endl;
        std::vector<string> column_list = get_column_list(reader);
#ifdef NOFOREACH
        BOOST_FOREACH(auto c,reader)
#else
        for(auto names: column_list)
#endif
            ss<<names<<std::endl;
        
        throw key_error(EXCEPTION_RECORD,ss.str());
    }
    catch(...)
    {   
        std::stringstream ss;
        ss<<"Error reading data from column ["<<cname<<"]!"<<std::endl;;
        throw file_error(EXCEPTION_RECORD,ss.str());
    }
    
    return data;
}


//-----------------------------------------------------------------------------
void read_from_file(const string &ifile,operation::array_type &channels,
                    operation::array_type &data,const string &xcol_name,
                    const string &ycol_name)
{
    //do here some checks with the file
    file f(ifile);
    if(!(f.extension() == ".fio"))
        throw file_error(EXCEPTION_RECORD,"Not a FIO file!");

    fio_reader reader;
    //read data from a file
    try{
        reader = fio_reader(ifile); 
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Error reading file "+ifile+"!");
    }

    string xcolumn = xcol_name;
    string ycolumn = ycol_name;

    //if no ycolumn name is given and the file contains more than one row 
    //we have to abort as we do not no which column to choose for MCA data
    if(ycolumn.empty())
    {
        if(reader.ncolumns() != 1)
        {
            std::stringstream ss;
            ss<<"File "<<ifile<<" contains more than one ";
            ss<<"columns - specify from which to read MCA data!";
            ss<<std::endl;
            
            throw file_error(EXCEPTION_RECORD,ss.str());
        }

        //if the file contains only one column and no ycolumn name has been
        //given by the use we can assume that this single column holds the 
        //MCA data
        ycolumn = reader.begin()->name();
    }

    //read MCA data
    data = read_column(ycolumn,reader);

    //perform some other check
    //if the xcolumn name is set and the file contains only one column something
    //is wrong
    if(xcolumn.empty())
        //if no channel column name has been passed by the user - create the
        //channel data automatically
        channels = create_channel_data(data.size());
    else
    {
        //if the user has passed a name for the channel column but the file has
        //only one folumn throw an exception
        if(reader.ncolumns() == 1)
        {
            std::stringstream ss;
            ss<<"The file contains only one columne - explicitely passing ";
            ss<<"a channel column name does not make sense!"<<std::endl;
            throw file_error(EXCEPTION_RECORD,ss.str());
        }
        
        //read the data from the file
        channels = read_column(xcolumn,reader);
    }
}

//-----------------------------------------------------------------------------
void read_from_stdin(operation::array_type &channels,operation::array_type &data)
{
    typedef operation::array_type array_type;
    typedef array_type::value_type value_type;
    std::vector<value_type> chvec,dvec;
    value_type ch,d;

    //need to figure out whether we have 

    while(std::cin>>ch>>d)
    {
        chvec.push_back(ch);
        dvec.push_back(d);
    }

    channels = array_type(operation::shape_type{chvec.size()});
    data     = array_type(operation::shape_type{chvec.size()});
    std::copy(chvec.begin(),chvec.end(),channels.begin());
    std::copy(dvec.begin() ,dvec.end() ,data.begin());
}

//-----------------------------------------------------------------------------
operation::array_type create_channel_data(size_t n)
{
    operation::array_type channels(operation::shape_type({n}));

    for(size_t i=0;i<n;i++) channels[i] = float64(i);
    return channels;
}
