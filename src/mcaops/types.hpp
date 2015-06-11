//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Jun 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

//!
//! \ingroup mcaops_devel
//! \brief array type 
//!
//! All data is stored in a dynamic array with element type float64
typedef pni::core::dynamic_array<pni::core::float64> data_array;

//!
//! \ingroup mcaops_devel
//! Constant iterator type
typedef array_type::const_iterator const_data_iterator;
typedef array_type::iterator       data_iterator;

//!
//! \ingroup mcaops_devel
//! General template for a data range. Sucha range consists of two iterators
//! marking the begin and end of the range. A data range can easily be used 
//! in particular with iterators. 
template<typename ITERT>
using data_range_t = std::pair<ITERT,ITERT>;

typedef data_range_t<const_data_iterator> const_data_range;
typedef data_range_t<data_iterator>       data_range;


