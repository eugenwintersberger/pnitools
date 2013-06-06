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
 * Created on: Jun 5,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

//include header files
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/image_reader.hpp>
#include <pni/io/image_info.hpp>
#include "../common/file.hpp"
#include "../common/exceptions.hpp"
#include <boost/filesystem.hpp> 

//setting namespaces
using namespace pni::io::nx;
using namespace pni::core;
namespace fs = boost::filesystem;

typedef std::vector<string> string_vector;
typedef std::list<string> string_list;
typedef std::list<file> file_list;
typedef std::unique_ptr<pni::io::image_reader> reader_ptr;

//-----------------utility functions-------------------------------------------
/*!
\ingroup det2nx_devel
\brief create configuration
 
Function creating the program configuration. 
\return instance of config
*/
configuration create_configuration();


//-----------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief open output file

Opens the file wher the data should be stored. 
\param fname name of the output file
\return an instance of nxfile
*/
h5::nxfile open_output_file(const string &fname);

//-----------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief get reader

Obtains the reader from the first image in the stack.
\throws file_type_errror in case of an unsupported input file type
\param flist list of input files
\param cbf_exts list of extensions for CBF
\param tiff_exts list of extensions for TIFF
\return unique pointer to reader object
*/
reader_ptr get_reader(const file_list &flist,const string_list &cbf_exts,
                      const string_list &tiff_exts);

//-----------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief retrieve image information

Get the image information for a particular file and channel. By default the
channel is 0 (the first image channel).
\param reader pointer to the reader for the image
\param path image file path
\param image_nr image index in the file
*/
pni::io::image_info get_image_info(reader_ptr &reader,const string &path,
                                   size_t image_nr=0);


//---------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief check input files 

All input files must be checked if they have the same shape and data type. 
This should be done in advance before the processing starts in order to avoid
accidental stops after a lot of images (and thus time). 
\throws type_error in case of a type missmatch
\throws shape_missmatch_error in case of a shape missmatch
\param flist input file list
\param reader unique pointer to the reader object
\param ref_info reference image info that all other images must match
\param image_nr index of the image in the file
\param channel_nr channel within the image
*/
void check_input_files(const file_list &flist,reader_ptr &reader,
                       const pni::io::image_info &ref_info,
                       size_t image_nr=0,size_t channel_nr=0);
