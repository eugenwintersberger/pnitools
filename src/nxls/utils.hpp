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
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nexus.hpp>
#include <pni/core/configuration.hpp>


//!
//! @ingroup nxls_devel
//! @brief get object path
//!
//! Return the path to the root object for nxls. If retrieving the path fails 
//! this function will abort the program.
//!
//! @param config configuration object
//!
pni::io::nexus::Path get_base_path(const pni::core::configuration &config);

//-----------------------------------------------------------------------------
//!
//! @ingroup nxls_devel
//! @brief get file
//!
//! Return the requested file. If anything goes wrong during opening the 
//! file the program is aborted.
//! 
//! @param path Nexus path with file portion
//! @return instance of h5::nxfile
//!
hdf5::file::File get_file(const pni::io::nexus::Path &path);

//----------------------------------------------------------------------------
//!
//! @ingroup nxls_devel
//! @brief get root object
//!
//! Returns the root object requested by the user from which the output 
//! should start. If this object cannot be found the program is aborted.
//!
//! There is currently one limitation: the base object must not be a
//! link. This might be fixed in a future version of the program.
//! 
//! @param file the input file
//! @param path the path refering to the root object
//! @return root object form which to start the interation
//!
pni::io::nexus::PathObject get_base(const hdf5::file::File &file,
                                    const pni::io::nexus::Path &base_path);
