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
#include <pni/io/cbf_reader.hpp>
#include <pni/io/tiff_reader.hpp>
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
h5::nxfile open_output_file(const string &fname,bool overwrite);

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

//-----------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief get the data field

This function returns the field to which the image data should be added. 
\param ofile ouput nexus file
\param info image information 
\param path nexus path to the field
\param deflate compression level for deflate filter
\return data field
*/
h5::nxfield get_field(const h5::nxfile &ofile,const pni::io::image_info &info,
                      const nxpath &path,size_t deflate); 

//-----------------------------------------------------------------------------
template<typename RTYPE> 
void append_data(RTYPE &&reader,const h5::nxfile &file,
                 h5::nxfield &field,const file_list &ifiles)
{
    if(field.type_id() == type_id_t::UINT8)
        append_data<uint8>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::INT8)
        append_data<int8>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::UINT16)
        append_data<uint16>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::INT16)
        append_data<int16>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::UINT32)
        append_data<uint32>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::INT32)
        append_data<int32>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::UINT64)
        append_data<uint64>(reader,file,field,ifiles);
    else if(field.type_id() == type_id_t::INT64)
        append_data<int64>(reader,file,field,ifiles);
}

//-----------------------------------------------------------------------------
template<typename T,typename RTYPE>
void append_data(RTYPE &&reader,const h5::nxfile &file,
                 h5::nxfield &field,const file_list &ifiles)
{
    //find the start index
    auto shape = field.shape<shape_t>();
    size_t frame_index = shape[0];
    size_t nx = shape[1];
    size_t ny = shape[2];

    //create a buffer for the data
    dbuffer<T> buffer(nx*ny);

    //iterate over all files
    for(auto f: ifiles)
    {
        if((frame_index % 100)  == 0)
            std::cout<<"storing frame "<<frame_index<<" ..."<<std::endl;

        reader.filename(f.path());
        reader.open();
        reader.image(buffer,0,0);
        
        field.grow(0);
        field(frame_index++,slice(0,nx),slice(0,ny)).write(buffer);
        file.flush();
        reader.close();
    }
}
