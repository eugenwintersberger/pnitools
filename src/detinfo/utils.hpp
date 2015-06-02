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
// Created on: Oct 7,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/configuration.hpp>
#include "types.hpp"
#include "detector_info.hpp"
#include "output_formatter.hpp"

using namespace pni::core;


//----------------------------------------------------------------------------
//!
//! \brief get detector information
//! 
//! \throws file_error if the file type is unkown
//! 
detector_info_list get_info(const file &f);

//----------------------------------------------------------------------------
//!
//! \brief get output formatter
//!
//! This function returns the output formatter according to the user 
//! configuration. If no appropriate output formatter is found an exception
//! is thrown and the program is aborted using std::exit with return value 1.
//!
//! \param config reference to the user configuration
//! \return pointer to the formatter instance
//!
output_formatter *get_output_formatter(const configuration &config);

//----------------------------------------------------------------------------
//!
//! \brief get input files
//!
//! This function creates the list of input files from the user provided 
//! configuration. 
//! If this operation fails the program is terminated with std::exit and a
//! return value of 1. 
//!
//! \param config user configuration
//! \return list of input files
//!
file_list get_input_files(const configuration &config);
