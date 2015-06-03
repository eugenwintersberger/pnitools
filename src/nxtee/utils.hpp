//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: Jun 3, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/core/configuration.hpp>

//!
//! \ingroup nxtee_devel
//! \brief generate the program configuration
//!
//! \return configuration instance
pni::core::configuration create_global_config();

//----------------------------------------------------------------------------
//!
//! \ingroup nxtee_devel
//! \brief show help if requested
//! 
//! Returns true if the user has requested help by passing -h or --help
//! to the program. In addition the help text is written to standard error.
//! 
//! \param config parsed program configuration
//! \return true if user requested help, false otherwise
//!
bool show_help(const pni::core::configuration &config);

//----------------------------------------------------------------------------
//!
//! \ingroup nextee_devel
//! \brief check if user provided a target path
//! 
//! Returns true if the user has not provided a target path. In the case 
//! the program should terminate as there is no location where to store the
//! data.
//! 
//! \param config parsed program configuration
//! \return true if not target path was provided, false otherwise
//!
bool no_target_path(const pni::core::configuration &config);

//----------------------------------------------------------------------------
//!
//! \ingroup nxtee_devel
//! \brief get the input file
//! 
//! Open the input file and return true on success. In case of errors the 
//! error message is written to standard error and false is returned. 
//! In the latter case the expected program behaviour would be to abort.
//! 
//! \param path the path to the target object (including the filename)
//! \param file non-const reference to the file
//! 
//! \return true if successful, false otherwise
//!
bool get_target_file(const pni::io::nx::nxpath &path,
                     pni::io::nx::h5::nxfile &file);

//----------------------------------------------------------------------------
//!
//! \ingroup nxtee_devel
//! \brief get target object
//! 
//! Open the target object (which can be either an attribute or a field) and 
//! returns true on success and false in any other case. In case of errors the 
//! error message is written to standard output. 
//!
//! \param path  the path to the target object
//! \param file reference to the NeXus file
//! \param target non-const reference to the target object
//! \return true if successful, false otherwise
//!
bool get_target_object(const pni::io::nx::nxpath &path,
                       const pni::io::nx::h5::nxfile &file,
                       pni::io::nx::h5::nxobject &target);
