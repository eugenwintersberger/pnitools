//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
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
// ============================================================================
//  Created on: Sep 30, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>

using namespace pni::core;

//---------------------------------------------------------------------
//!
//! \brief initialize cell
//!
//! Initialize a scalar type column cell. The first argument is the 
//! shape of the cell element which is ignored in this case - a scalar 
//! has no shape.
//!
//! \tparam T scalar data type
//! \param s shape of the elements 
//! \param init_value initial value for each cell
//! \param cell reference to the cell
//!
template<typename T>
void init_cell(const shape_t &s, T init_value, scalar<T> &cell)
{
    cell = T(init_value); 
}

//---------------------------------------------------------------------
//!
//! \brief initialize cell
//! 
//! Initialize a cell which is of a STL container type. The data type 
//! of the initial value is derived from the value_type member type 
//! of the container. Only the first element in the shape argument
//! is used - it is treated as the size of the container.
//! 
//! \tparam CTYPE STL container type
//! \param s shape
//! \param init_value initial value for the cell 
//! \param cell refernece to the cell
//! 
template<typename CT >
void init_cell(const shape_t &s,typename CT::value_type init_value, 
               CT &cell)
{
    cell = CT(s.at(0));
    std::fill(cell.begin(),cell.end(),init_value);
}

//----------------------------------------------------------------------
//! 
//! \brief initialize cell
//! 
//! Initialize a column cell of type mdarray. The type of the initial
//! value is determined by the value_type member type of the mdarray
//! instance.
//!
//! \tparam OTYPES template parameters for mdarray
//! \param s shape of the array
//! \param init_value initial value of the cell
//! \param cell reference to the cell
//! 
template<typename ...OTYPES>
void init_cell(const shape_t &s,
               typename mdarray<OTYPES...>::value_type init_value,
               mdarray<OTYPES...> &cell)
{
    cell = mdarray<OTYPES...>::create(s);
    std::fill(cell.begin(),cell.end(),init_value);
}

//---------------------------------------------------------------------
//!
//! \brief initialize cell
//! 
//! Initialize a cell of type array (the type erasure for mdarray). 
//! The data type to be stored depends on the initial value passed 
//! to the template. 
//! 
//! \tparam T data type of the initial value
//! \param s shape of the array
//! \param init_value initial value
//! \param cell reference to the cell
//!
template<typename T>
void init_cell(const shape_t &s,T init_value,array &cell)
{
    typedef dynamic_array<T> array_t;

    array_t a = array_t::create(s);
    std::fill(a.begin(),a.end(),init_value);
    cell = array(a);
}
