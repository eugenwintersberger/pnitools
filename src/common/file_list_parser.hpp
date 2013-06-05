/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jun 5, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>
#include <list>
#include "file.hpp"
#include <boost/tokenizer.hpp>
#include <boost/format.hpp>

using namespace pni::core;


/*!
\ingroup common_devel
\brief parser for file lists

This class provides a static function to parse containers of strings which
either represent single files or file ranges and assembles a list of file
objects from this. 
\code{.cpp}
typedef std::list<file> file_list;
....
std::vector<string> fnames = {"test_%i.dat:1:100","test_1111.dat","test_0.dat"};
....
auto files = file_list_parser::parse<file_list>(fnames);
\endcode
*/
class file_list_parser
{
    private:
        //! separator type for numeric ranges
        typedef boost::char_separator<char> nrseparator;
        //! tokenizer type for numeric ranges
        typedef boost::tokenizer<nrseparator> nrtokenizer;

        /*!
        \brief add files from range
        
        Adds files from a file range to a file container.
        \tparam CTYPE container type for the files
        \param po path string (template)
        \param flist instance of CTYPE where to append the files
        */
        template<typename CTYPE>
        static bool _fill_from_num_range(const string &po,CTYPE &flist);
    
    public:
        //------------------------------------------------------------------
        /*! 
        \brief parser method
       
        Static method to parse a container of file names and file ranges and
        returns another container with files.
        \tparam ITYPE input container type
        \tparam OTYPE output container type
        \param pl instance of ITPYE with file names and ranges
        \return instance of OTYPE with files
        */
        template<typename OTYPE,typename ITYPE> 
            static OTYPE parse(const ITYPE &pl)
        {
            OTYPE flist;
            for(auto po: pl)
            {
                if(!_fill_from_num_range(po,flist))
                    flist.push_back(po);
            }

            return flist;
        }
};

//-----------------------------------------------------------------------------
template<typename CTYPE> 
bool file_list_parser::_fill_from_num_range(const string &p,CTYPE &flist)
{

    nrseparator sep(":");
    nrtokenizer token(p,sep);
    size_t start = 0;
    size_t stop = 0;
    size_t stride = 1;
    string p_template;

    size_t index = 0;
    for(auto iter = token.begin(); iter!= token.end();++iter)
    {
        std::stringstream ss(*iter);
        switch(index)
        {
            case 0: ss>>p_template; break;
            case 1: ss>>start; break;
            case 2: ss>>stop; break;
            case 3: ss>>stride; break;
        }
        index++;
    }

    if(index<2) return false;

    index = start;
    do
    {
        std::stringstream ss;
        ss<<boost::format(p_template)%index;
        flist.push_back(ss.str());
        index += stride;

    }while(index<=stop);
    
    return true;
}
