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
 * Created on: Nov 12, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <map>
#include <cctype>
#include <algorithm>
#include <functional>
#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/tiff/tiff_reader.hpp>
#include "file.hpp"
#include "file_list_parser.hpp"

//-----------------------------------------------------------------------------
//!
//! \brief extension to type map
//! 
//! This map provides an easy way to map file extensions to file types. It is 
//! mainly used to select the appropriate reader.
//!
static std::map<string,string> type_extension_map = 
    {{".cbf","cbf"},
     {".tif","tif"},
     {".tiff","tif"}};

//-----------------------------------------------------------------------------
//!
//! \brief read data 
//! 
//! This template function takes a pointer to a reader and reads the data 
//! from the file. Data is read in its native data type and later converted 
//! to the value_type of image_type. One should have a look if this 
//! causes significant performance penalties. 
//! 
//! \throws file_error in case of IO problems
//! \throws memory_allocation_error if the amount of memory required to store 
//! the data cannot be allocated 
//! \param reader unique pointer to the reader object
//! \return instance of image_type with image data
//!
template<typename ITYPE,typename RTYPE> ITYPE read_data(RTYPE &&reader)
{
    typedef typename ITYPE::storage_type storage_type;

    //get image information
    pni::io::image_info info = reader.info(0);

    return ITYPE(shape_t{info.nx(),info.ny()},
                 reader.template image<storage_type>(0,0));
    
}

//-----------------------------------------------------------------------------
//!
//! \brief read an image from a file
//! 
//! Function reading a single image from a file. 
//! \throws file_error in case of IO errors
//! \tparam ITYPE image type
//! \param f input file
//! \return instance of image_type with image data
//! 
template<typename ITYPE> ITYPE read_image(const file &infile)
{
    //determine the reader type from the file extension
    pni::core::string type;
    try
    {
        pni::core::string extension = infile.extension();
        std::transform(extension.begin(),extension.end(),extension.begin(),
                       std::ptr_fun<int,int>(std::tolower));
        type = type_extension_map[extension];
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Unable to determine file type for file "+infile.path()+ "!");
    }

    try
    {
        if(type == "cbf")
            return read_data<ITYPE>(cbf_reader(infile.path()));
        else if(type == "tif")
            return read_data<ITYPE>(tiff_reader(infile.path()));
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Unable to construct reader for file "+infile.path()+"!");
    }
}

template<typename ITYPE> ITYPE read_image(const pni::core::string &fname)
{
    return read_image<ITYPE>(file(fname));
}


