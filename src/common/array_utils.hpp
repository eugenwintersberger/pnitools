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
// ==========================================================================-
// Created on: Jun 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#pragma once

#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>

using namespace pni::core;

//!
//! \ingroup common_devel
//! \brief create array 
//! 
//! Creates an array type erasure of a type determined by tid and a particular
//! shape. The underlying storage type is a darray<T,dbuffer<T>> instance. 
//! \throws type_error if tid referes to an unsupported type
//! \param tid type id 
//! \param shape the shape of the array
//! \return instance of array
//!
array create_array(type_id_t tid,const shape_t &shape);
