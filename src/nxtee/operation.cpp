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
//************************************************************************
// Created on: Jun 3, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/algorithms/get_type.hpp>
#include "operation.hpp"
#include "appender.hpp"
#include "replacer.hpp"

using namespace pni::core;
using namespace pni::io::nx;

void append(h5::nxobject &target)
{
    switch(get_type(target))
    {
        case type_id_t::UINT8:      appender<uint8>()(target);      break;
        case type_id_t::INT8:       appender<int8>()(target);       break;
        case type_id_t::UINT16:     appender<uint16>()(target);     break;
        case type_id_t::INT16:      appender<int16>()(target);      break;
        case type_id_t::UINT32:     appender<uint32>()(target);     break;
        case type_id_t::INT32:      appender<int32>()(target);      break;
        case type_id_t::UINT64:     appender<uint64>()(target);     break;
        case type_id_t::INT64:      appender<int64>()(target);      break;
        case type_id_t::FLOAT32:    appender<float32>()(target);    break;
        case type_id_t::FLOAT64:    appender<float64>()(target);    break;
        case type_id_t::FLOAT128:   appender<float128>()(target);   break;
        case type_id_t::COMPLEX32:  appender<complex32>()(target);  break;
        case type_id_t::COMPLEX64:  appender<complex64>()(target);  break;
        case type_id_t::COMPLEX128: appender<complex128>()(target); break;
        case type_id_t::BOOL:       appender<bool_t>()(target);     break;
        case type_id_t::STRING:     appender<string>()(target);     break;
        default:
            throw type_error(EXCEPTION_RECORD,
                    "Cannot handle target object data type!");
    };
}

template<typename T> void replace(h5::nxobject &target,size_t index_offset)
{
    replacer<T> r(index_offset);
    r(target);
}

//----------------------------------------------------------------------------
void replace(h5::nxobject &target,size_t index_offset)
{
    switch(get_type(target))
    {
        case type_id_t::UINT8:      
            replace<uint8>(target,index_offset);      break;
        case type_id_t::INT8:       
            replace<int8>(target,index_offset);       break;
        case type_id_t::UINT16:     
            replace<uint16>(target,index_offset);     break;
        case type_id_t::INT16:      
            replace<int16>(target,index_offset);      break;
        case type_id_t::UINT32:     
            replace<uint32>(target,index_offset);     break;
        case type_id_t::INT32:      
            replace<int32>(target,index_offset);      break;
        case type_id_t::UINT64:     
            replace<uint64>(target,index_offset);     break;
        case type_id_t::INT64:      
            replace<int64>(target,index_offset);      break;
        case type_id_t::FLOAT32:    
            replace<float32>(target,index_offset);    break;
        case type_id_t::FLOAT64:    
            replace<float64>(target,index_offset);    break;
        case type_id_t::FLOAT128:   
            replace<float128>(target,index_offset);   break;
        case type_id_t::COMPLEX32:  
            replace<complex32>(target,index_offset);  break;
        case type_id_t::COMPLEX64:  
            replace<complex64>(target,index_offset);  break;
        case type_id_t::COMPLEX128: 
            replace<complex128>(target,index_offset); break;
        case type_id_t::BOOL:       
            replace<bool_t>(target,index_offset);     break;
        case type_id_t::STRING:     
            replace<string>(target,index_offset);     break;
        default:
            throw type_error(EXCEPTION_RECORD,
                    "Cannot handle target object data type!");
    };
}
