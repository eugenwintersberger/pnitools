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
#include <pni/core/config/configuration.hpp>
#include <pni/io/tiff/tiff_reader.hpp>
#include "types.hpp"
#include "../common/file.hpp"
#include "../common/file_list_parser.hpp"

using namespace pni::io;

//list of file names
typedef std::vector<string> file_name_list;
//list of file objects
typedef std::vector<file> file_list;

/*!
\brief unique pointer to reader 

A unique pointer to a reader instance. Readers must not be shared thus a unique
pointer is the appropriate data structure to guard the pointer. 
*/
typedef std::unique_ptr<image_reader> reader_ptr;

//-----------------------------------------------------------------------------
/*!
\brief extension to type map

This map provides an easy way to map file extensions to file types. It is mainly
used to select the appropriate reader.
*/
static std::map<string,string> type_extension_map = 
    {{".cbf","cbf"},
     {".tif","tif"},
     {".tiff","tif"}};

//-----------------------------------------------------------------------------
/*!
\brief read an image from a file

Function reading a single image from a file. 
\throws file_error in case of IO errors
\param f input file
\return instance of image_type with image data
*/
image_type read_image(const file &f);

//-----------------------------------------------------------------------------
/*!
\brief get the darkfield image 

Reads the darkfield image if present in the current program configuration. 
If no darkfield is requested by the use an empty image is returned. 

\throws file_error if reading image data fails 
\param config program configuration
\return instance of image_type with darkfield image
*/
image_type get_darkfield(const configuration &config);

//-----------------------------------------------------------------------------
/*!
\brief get the list of input files

This function reads the list of input files from the command line configuration.
If no input files are given an exception will be thrown. Additionally an
exception is thrown if one of the files is not a regular file. 

\throws cli_option_error if no input files are given
\throws file_error at least one of the files is not a regular file
\param config current program configuration
\return instance of file_list with the input files
*/
file_list get_input_files(const configuration &config);

//-----------------------------------------------------------------------------
/*!
\brief get flatfield image

Reads the flatfield image if requested by the current program configuration. If
no floatfield is requested by the user an empty image is returned. 

\throws file_error in case of errors during reading the data
\param config current program configuration
\return instance of image_type with flatfield data
*/
image_type get_flatfield(const configuration &config);


//-----------------------------------------------------------------------------
/*!
\brief read data 

This template function takes a pointer to a reader and reads the data from the
file. Data is read in its native data type and later converted to the value_type
of image_type. One should have a look if this causes significant performance
penalties. 

\throws file_error in case of IO problems
\throws memory_allocation_error if the amount of memory required to store the
data cannot be allocated 
\param reader unique pointer to the reader object
\return instance of image_type with image data
*/
template<typename RTYPE> image_type read_data(RTYPE &&reader)
{
    typedef image_type::storage_type storage_type;

    //get image information
    image_info info = reader.info(0);

    //create the output image
    shape_t shape{info.nx(),info.ny()};
    
    //read data from the file
    auto data = reader.template image<storage_type>(0,0);

    //return the output image
    return image_type(std::move(shape),std::move(data));
}

