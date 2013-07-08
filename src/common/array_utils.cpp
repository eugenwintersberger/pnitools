/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jun 5, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/core/darray.hpp>
#include <pni/core/dbuffer.hpp>
#include <pni/core/exceptions.hpp>
#include "array_utils.hpp"


array create_array(type_id_t tid,const shape_t &shape)
{
    if(tid == type_id_t::UINT8)
        return array(darray<uint8,dbuffer<uint8>>(shape));
    else if(tid == type_id_t::INT8)
        return array(darray<int8,dbuffer<int8>>(shape));
    else if(tid == type_id_t::UINT16)
        return array(darray<uint16,dbuffer<uint16>>(shape));
    else if(tid == type_id_t::INT16)
        return array(darray<int16,dbuffer<int16>>(shape));
    else if(tid == type_id_t::UINT32)
        return array(darray<uint32,dbuffer<uint32>>(shape));
    else if(tid == type_id_t::INT32)
        return array(darray<int32,dbuffer<int32>>(shape));
    else if(tid == type_id_t::UINT64)
        return array(darray<uint64,dbuffer<uint64>>(shape));
    else if(tid == type_id_t::INT64)
        return array(darray<int64,dbuffer<int64>>(shape));
    else if(tid == type_id_t::FLOAT32)
        return array(darray<float32,dbuffer<float32>>(shape));
    else if(tid == type_id_t::FLOAT64)
        return array(darray<float64,dbuffer<float64>>(shape));
    else if(tid == type_id_t::FLOAT128)
        return array(darray<float128,dbuffer<float128>>(shape));
    else if(tid == type_id_t::STRING)
        return array(darray<string,dbuffer<string>>(shape));
    else
        throw type_error(EXCEPTION_RECORD,
                "unsupported data type!");
}
