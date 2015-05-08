//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Oct 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "types.hpp"
#include <pni/core/configuration.hpp>
#include <pni/io/image_info.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/get_type.hpp>

using namespace pni::io::nx;


//!
//! \ingroup det2nx_devel
//! \brief get input files
//!
//! Extracts a list of input files from the program configuration.
//!
//! \throws program_error in case of an error
//! \param config program configuration
//! \return list with input files
//!
file_list get_input_files(const configuration &config);

//-----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief get image information
//!
//! Retrieves the image information from the first file in the input file list.
//!
//! \throws program_error in case of an error
image_info get_image_info(const file_list &input_files);

//-----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief get detector path
//!
//! This function returns the path to the detector group where the data should 
//! be stored. 
//!
//! \throws program_error in case of an error
//! \param config program configuration
//! \return Nexus path object
//! 
nxpath get_detector_path(const configuration &config);

//-----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief open output file
//! 
//! Open the detector file. 
//!
//! \throws program_error in case of an error
//! \param detector_path path to the detector group
//! \return an instance of nxfile
//!
h5::nxfile open_detector_file(const nxpath &detector_path);

//----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief open detector group
//!
//! The program assumes that the detector group exists and tries to open it.
//!
//! \throws program_error in the case of errors
//! \param detector_file the file holding the detector
//! \param detector_path path to the detector group
//! \return group instance
//!
h5::nxgroup get_detector_group(const h5::nxfile &detector_file,
                               const nxpath &detector_path);

//---------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief get detector field
//!
//! This is an essential function in this program.  It retrieves the detector
//! field from the detector group. There are three possibilities how
//! this is done
//! \li the field does not exist - a new one will be created according to 
//!     the image information
//! \li the field exists and its shape and data type match the image 
//!     information - in this case the data will be appended
//! \li the field exists and shape and datatype doe not match
//!     in this case we check the size of the field. If the field is 
//!     empty (size=0) it will be removed and a new one with appropriate
//!     shape and data type is created. If the field has a finite size 
//!     the program will be aborted.
//! 
//! 
h5::nxfield get_detector_field(const h5::nxgroup &detector_group, 
                               const pni::io::image_info &info,
                               const configuration &config);

//----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief append data to the field
//!
//! This function implementes the infrastructure sequence for appending 
//! data to the field. If the operation fails the program will be 
//! aborted.
//!
//! \params file the output file
//! \params field the field where to store the data
//! \params files input files
//! 
void append_data(h5::nxfile &file, h5::nxfield &field,
                 const file_list &files);

//-----------------------------------------------------------------------------
template<typename RTYPE> 
void append_data(RTYPE &&reader,const h5::nxfile &file,
                 h5::nxfield &field,const file_list &ifiles)
{
    if(get_type(field) == type_id_t::UINT8)
        append_data<uint8>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::INT8)
        append_data<int8>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::UINT16)
        append_data<uint16>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::INT16)
        append_data<int16>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::UINT32)
        append_data<uint32>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::INT32)
        append_data<int32>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::UINT64)
        append_data<uint64>(reader,file,field,ifiles);
    else if(get_type(field) == type_id_t::INT64)
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
    auto buffer = dynamic_array<T>::create(shape);

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
