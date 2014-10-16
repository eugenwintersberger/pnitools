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
#include <pni/io/nx/nx.hpp>

using namespace pni::io::nx;

//!
//! \ingroup det2nx_devel
//! \brief get input files
//!
//! Extracts a list of input files from the program configuration.
//! If this function fails the program will be aborted.
//!
//! \param config program configuration
//! \return list with input files
//!
file_list get_input_files(const configuration &config);

//-----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief get detector path
//!
//! This function returns the path to the detector group where the data should 
//! be stored. If this operation fails the program will be aborted.
//! 
//! \param config program configuration
//! \return Nexus path object
//! 
nxpath get_detector_path(const configuration &config);

//-----------------------------------------------------------------------------
//!
//! \ingroup det2nx_devel
//! \brief open output file
//! 
//! Open the detector file. If this operation fails the program will be 
//! aborted.
//!
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
//! If this operation fails the program will be aborted. 
//!
//! \param detector_file the file holding the detector
//! \param detector_path path to the detector group
//! \return group instance
//!
h5::nxgroup get_detector_group(const h5::nxfile &detector_file,
                               const nxpath &detector_path);
