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

using namespace pni::core;

configuration create_configuration();

//----------------------------------------------------------------------------
//!
//! \brief parse command line configuration
//!
//! This function parsers the command line options provided by the user and
//! returns the resulting configuration.
//! In case of an error the function aborts the entire program using
//! std::exit(1) and returns 1 to the calling shell.
//!
//! \param argc number of command line arguments and options
//! \param argv arguments and options
//! \return instance of configuration
//!
bool parse_configuration(int argc,char **argv,configuration &config);
