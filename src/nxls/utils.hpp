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

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/core/configuration.hpp>
using namespace pni::io::nx;
using namespace pni::core;

#include "output_config.hpp"

//!
//! \brief get object path
//!
//! Return the path to the root object for nxls. If retrieving the path fails 
//! this function will abort the program.
//!
//! \param config configuration object
nxpath get_path(const configuration &config);

//-----------------------------------------------------------------------------
//!
//! \brief get file
//!
//! Return the requested file. If anything goes wrong during opening the 
//! file the program is aborted.
//! 
//! \param path Nexus path with file portion
//! \return instance of h5::nxfile
//!
h5::nxfile get_file(const nxpath &path);

//----------------------------------------------------------------------------
//!
//! \brief get root object
//!
//! Returns the root object requested by the user from which the output 
//! should start. If this object cannot be found the program is aborted.
//! 
//! 
h5::nxobject get_root(const h5::nxfile &file,const nxpath &path);

//----------------------------------------------------------------------------
//!
//! \brief construct output configuration
//! 
//! Construct the output configuration from command line options. 
//! 
//! \param path path to the root object
//! \return instance of output_config
//!
output_config make_output_config(const configuration &config);
