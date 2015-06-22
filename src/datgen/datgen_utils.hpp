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
// ===========================================================================
// Created on: Jun 9, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include "grid_generator.hpp"
#include "options_splitter.hpp"
#include "functors/executor.hpp"

//!
//! \ingroup datgen_devel
//! \brief create global configuration
//!
//! Utilty function creating the global configuration for the datgen 
//! program. 
//!
//! \return configuration instance
//!
pni::core::configuration create_global_config();

//!
//! \ingroup datgen_devel
//! \brief read type id an input stream
//!
//! This is a special version of the input stream operator for type IDs. 
//! It basically handles only "int" and "float" which ware mapped to 
//! type_id_t::INT64 and type_id_t::FLOAT64. All other input causes a 
//! type_error exception to be thrown.
//!
//! Need to do this in namespace std:: for the same reason as I have to 
//! do this for the slice input operator in mcaops_utils.hpp.
//!
//! \throws type_error in case of an unkown type code
//! \param stream reference to input stream
//! \param tid reference to type_id value
//! \return reference to input stream
//!
namespace std{
    istream &operator>>(istream &stream,pni::core::type_id_t &tid);
}

//!
//! \ingroup datgen_devel
//! \brief show help text on user request 
//! 
//! Prints the help text when the user starts the program with -h or 
//! --help. The function returns true if help is shown. 
//! This should be used as an indicator that the program should 
//! abort.
//! 
//! \param global_config reference to the global configuration of the
//!                      program
//! \return true if showing help, false otherwise
bool show_help(const pni::core::configuration &global_config);

//----------------------------------------------------------------------------
//! 
//! \ingroup datgen_devel
//! \brief build the grid generator
//! 
//! Build the grid generator from the global program configuration. 
//! If the function returns false an error occured and the program should 
//! bort. 
//! 
//! \param global_config reference to the program global configuration
//! \param generator reference to the grid_generator insance to create
//! \return true if everything is fine, false otherwise
//!
bool build_grid_generator(const pni::core::configuration &global_config,
                          grid_generator &generator);

//----------------------------------------------------------------------------
//! 
//! \ingroup datgen_devel
//! \brief build executor
//! 
//! Build the executor stack from the functors passed by the user to the 
//! command line of the program. The function returns true if everything went
//! fine. Otherwise false is returned.
//! 
//! \param arg_map argument map
//! \param exe reference to the executor
//! \return true if everything went find, false otherwise
bool build_executor(const args_map &,executor &);

//-----------------------------------------------------------------------------
//!
//! \ingroup datgen_devel
//! \brief check number of input arguments
//! 
//! Check if there are input arguments at all and if the functor names are
//! valid. If true everything is OK. If false the program should abort.
//! 
//! \param args input arguments map
//! \return true if everying is ok, flase otherwise
//! 
bool check_arguments(const args_map &args);

//----------------------------------------------------------------------------
//!
//! \ingroup datgen_devel
//! \brief parse global configuration
//! 
//! Parsers the global configuration provided by the user from the 
//! arguments map. It finally removes the 'globals' section from the 
//! arguments map. The function returns true if everything was ok, and 
//! false otherwise. If the return value is false the program should abort. 
//!
//! 
bool parse_global_config(pni::core::configuration &global_config,
                         args_map &args);

//
