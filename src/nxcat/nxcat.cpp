//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Jan 16,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "nxcat.hpp"
#include "../common/config_utils.hpp"


static const string prg_name = "nxcat";
static const string help_hdr = "nxcat usage:\t  nxcat [OPTIONS] INPUT FILES";

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    configuration conf = create_configuration();

    if(argc<2)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use nxcat -h for help  ..."<<std::endl;
        return 1;
    }

    if(parse_cli_opts(argc,argv,prg_name,conf))
        return 1;

    if(check_help_request(conf,help_hdr))
        return 1;


    sources_list sources;
    try
    {
        //----------------------parse the input data----------------------------
        //get the source string
        for(auto source_path: conf.value<StringList>("source"))
            sources.push_back(nxpath::from_string(source_path));

        //table with data
        table_t data_tab = read_table(sources);

        //obtain the list of column names
        auto keys = data_tab.keys<StringList>();

        //print the colunm names (the table headers) if requested by the
        //user
        if(conf.value<bool>("header"))
        {
            for(auto key: keys)
                std::cout<<"#"<<data_tab[key].name()<<" ("
                         <<data_tab[key].unit()<<")"<<std::endl;
        }

        //get start and stop indices
        size_t start_index = conf.value<size_t>("start");
        //if the stop index is 0 we print everything
        size_t end_index   = conf.value<size_t>("end")==0 ? data_tab.nrows() :
                             conf.value<size_t>("end");

        //loop over all rows
        for(size_t row_index=start_index;row_index<end_index;++row_index)
        {
            //loop over all columns - this is currently not very nice
            //but works and seems to be fast enough
            for(auto key: keys)
            {

                column_t::iterator iter = data_tab[key].begin();
                std::advance(iter,row_index);
                std::cout<<pni::io::format(*iter)<<"\t";
            }

            std::cout<<std::endl;
        }

    }
    catch(memory_not_allocated_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(shape_mismatch_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(type_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(key_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(size_mismatch_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Something went wrong!"<<std::endl;
        for(auto s: sources)
            std::cerr<<s<<std::endl;

        return 1;
    }

    return 0;
}
