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


