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
// Created on: Jun 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays/slice.hpp>
#include <pni/io/parsers/slice_parser.hpp>
#include <list>
#include "file.hpp"
#include <boost/format.hpp>
#include <iostream>


using namespace pni::core;


//!
//! \ingroup common_devel
//! \brief parser for file lists
//! 
//! This class provides a static function to parse containers of strings which
//! either represent single files or file ranges and assembles a list of file
//! objects from this. 
/*!\code{.cpp}
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

        //!
        //!\brief add files from range
        //! 
        //! Adds files from a file range to a file container.
        //!
        //! \tparam CTYPE container type for the files
        //! \param po path string (template)
        //! \param flist instance of CTYPE where to append the files
        //!
        template<typename CTYPE>
        static bool _fill_from_num_range(const pni::core::string &po,
                                         CTYPE &flist);
    
    public:
        //------------------------------------------------------------------
        //! 
        //! \brief parser method
        //! 
        //! Static method to parse a container of file names and file 
        //! ranges and returns another container with files.
        //!
        //! \tparam ITYPE input container type
        //! \tparam OTYPE output container type
        //! \param pl instance of ITPYE with file names and ranges
        //! \return instance of OTYPE with files
        //!
        template<
                 typename OTYPE,
                 typename ITYPE
                > 
        static OTYPE parse(const ITYPE &pl)
        {
            //check the value types of the input and output container types
            //provided by the user.
            static_assert(std::is_same<typename OTYPE::value_type,
                                       file>::value,
                          "Target container must store files!");
            static_assert(std::is_same<typename ITYPE::value_type,
                                       pni::core::string>::value,
                          "Source container must store string!");

            //--------------------------------------------
            // main loop
            //--------------------------------------------
            OTYPE flist;
            for(auto po: pl)
            {
                _fill_from_num_range(po,flist);
            }

            return flist;
        }
};

//-----------------------------------------------------------------------------
template<typename CTYPE> 
bool file_list_parser::_fill_from_num_range(const pni::core::string &p,
                                            CTYPE &flist)
{
    using parser_t = pni::io::parser<slice>;
    auto slice_first = std::find(p.begin(),p.end(),':');

    if(slice_first==p.end()) 
    {   //no slice section found - we can assume that the string is a single 
        //file and just add it to the list of files.
        flist.push_back(p);
        return true;
    }

    string filename_format(p.begin(),slice_first);
    std::advance(slice_first,1);
    string file_slice_str(slice_first,p.end());
    pni::core::slice file_slice;
    std::cout<<"Filename format: "<<filename_format<<std::endl;
    std::cout<<"Slice string: "<<file_slice_str<<std::endl;
    
    try
    {   
        parser_t pslice; 
        file_slice = pslice(file_slice_str);
    }
    catch(const pni::io::parser_error &error)
    {
        std::stringstream ss;
        ss<<"["<<p<<"] is not a valid file range!"<<std::endl;
        throw pni::io::parser_error(EXCEPTION_RECORD,ss.str());
    }

    for(size_t index = file_slice.first();index<file_slice.last();
               index += file_slice.stride())
    {
        std::stringstream ss;
        ss<<boost::format(filename_format)%index;
        std::cout<<"Added file: "<<ss.str()<<std::endl;
        flist.push_back(ss.str());
    }
    
    return true;
}
