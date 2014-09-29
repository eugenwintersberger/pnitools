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
// ===========================================================================
// Created on: Jun 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/arrays.hpp>
#include <pni/core/error.hpp>
#include "array_utils.hpp"


array create_array(type_id_t tid,const shape_t &shape)
{
    if(tid == type_id_t::UINT8)
        return array(dynamic_array<uint8>::create(shape));
    else if(tid == type_id_t::INT8)
        return array(dynamic_array<int8>::create(shape));
    else if(tid == type_id_t::UINT16)
        return array(dynamic_array<uint16>::create(shape));
    else if(tid == type_id_t::INT16)
        return array(dynamic_array<int16>::create(shape));
    else if(tid == type_id_t::UINT32)
        return array(dynamic_array<uint32>::create(shape));
    else if(tid == type_id_t::INT32)
        return array(dynamic_array<int32>::create(shape));
    else if(tid == type_id_t::UINT64)
        return array(dynamic_array<uint64>::create(shape));
    else if(tid == type_id_t::INT64)
        return array(dynamic_array<int64>::create(shape));
    else if(tid == type_id_t::FLOAT32)
        return array(dynamic_array<float32>::create(shape));
    else if(tid == type_id_t::FLOAT64)
        return array(dynamic_array<float64>::create(shape));
    else if(tid == type_id_t::FLOAT128)
        return array(dynamic_array<float128>::create(shape));
    else if(tid == type_id_t::STRING)
        return array(dynamic_array<string>::create(shape));
    else
        throw type_error(EXCEPTION_RECORD,
                "unsupported data type!");
}
