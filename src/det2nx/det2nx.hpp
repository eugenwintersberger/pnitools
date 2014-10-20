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
// Created on: Jun 5,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

//include header files
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/image_reader.hpp>
#include <pni/io/image_info.hpp>
#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/tiff/tiff_reader.hpp>
#include "../common/file.hpp"
#include "../common/exceptions.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

//setting namespaces
using namespace pni::io::nx;
using namespace pni::core;

typedef std::vector<string> string_vector;
typedef std::list<string> string_list;
typedef std::list<file> file_list;


//-----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! config/\brief get the data field
//! 
//! This function returns the field to which the image data should be added. 
//! \param nxobject_t variant instance of the parent object
//! \param info image information 
//! \param path nexus path to the field
//! \param deflate compression level for deflate filter
//! \return field as variant type
//!
h5::nxobject get_field(const h5::nxobject &parent,
                       const pni::io::image_info &info,
                       const nxpath &path,size_t deflate); 

