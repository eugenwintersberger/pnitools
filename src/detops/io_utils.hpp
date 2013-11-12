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
#include "types.hpp"
#include "../common/file.hpp"

using namespace pni::io;

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
\brief create reader object from file

Take a file object and return a unique pointer to the appropriate reader. If no
reader is found an exception will be thrown. 

\throws file_error if no appropriate reader is found 
\param infile input file as an instance of file
\return unique pointer to the reader instance
*/
reader_ptr reader_from_file(const file &infile);

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
template<typename T> image_type read_data(const reader_ptr &reader)
{
    typedef std::vector<T> buffer_type;

    //get image information
    image_info info = reader->info(0);

    //create the output image
    image_type image(shape_t{info.nx(),info.ny()});
    
    //read data from the file
    auto data = reader->image<buffer_type>(0,0);
    //copy data to the output image
    std::copy(data.begin(),data.end(),image.begin());

    return image;
}
