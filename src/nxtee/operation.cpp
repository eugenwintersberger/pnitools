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

#include "operation.hpp"
#include "appender.hpp"
#include "replacer.hpp"
#include "utils.hpp"

using namespace pni::core;
using namespace pni::io;

void append(nexus::PathObject &target)
{
  switch(get_type_id(target))
  {
    case type_id_t::UINT8:      Appender<uint8>()(target);      break;
    case type_id_t::INT8:       Appender<int8>()(target);       break;
    case type_id_t::UINT16:     Appender<uint16>()(target);     break;
    case type_id_t::INT16:      Appender<int16>()(target);      break;
    case type_id_t::UINT32:     Appender<uint32>()(target);     break;
    case type_id_t::INT32:      Appender<int32>()(target);      break;
    case type_id_t::UINT64:     Appender<uint64>()(target);     break;
    case type_id_t::INT64:      Appender<int64>()(target);      break;
    case type_id_t::FLOAT32:    Appender<float32>()(target);    break;
    case type_id_t::FLOAT64:    Appender<float64>()(target);    break;
    case type_id_t::FLOAT128:   Appender<float128>()(target);   break;
    case type_id_t::STRING:     Appender<string>()(target);     break;
    default:
      throw type_error(EXCEPTION_RECORD,
                       "Cannot handle target object data type!");
  };
}

template<typename T>
void replace(nexus::PathObject &target,size_t index_offset)
{
  Replacer<T> r(index_offset);
  r(target);
}

//----------------------------------------------------------------------------
void replace(nexus::PathObject &target,size_t index_offset)
{
  switch(get_type_id(target))
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
    case type_id_t::STRING:
      replace<string>(target,index_offset);     break;
    default:
      throw type_error(EXCEPTION_RECORD,
                       "Cannot handle target object data type!");
  };
}
