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
 * Created on: Jun 27, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

#include "nexus_group_utils.hpp"
#include "nxobject_traits.hpp"

using namespace pni::core;
using namespace pni::io::nx;

/*!
\ingroup common_devel
\brief get an existing field

Return an existing field according to a path object. 
\tparam GTYPE group type
\param p parent group 
\param path the field path relative to the parent
\param f field instance
*/
template<typename GTYPE>
typename nxobject_traits<GTYPE>::field_type 
get_field(const GTYPE &p,const nxpath &path)
{
    //here we assume that all elements in the path except the last one refer to
    //groups - create a new path with one element less
    nxpath group_path,field_path;
    split_last(path,group_path,field_path);

    GTYPE parent; 
    parent = get_group(p,group_path,false);

    return parent[field_path.begin()->first];

}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a field

Create a field from a type_id_t and a shape object. 
\throws type_error if data type is not supported
\tparam PTYPE parent type
\tparam STYPE shape type
\param parent instance of PTYPE - there parent object
\param name the name of the new field
\param tid type_id of the field
\param shape instance of STYPE - the shape of the field
\param field reference to the new field
*/
template<typename PTYPE,typename STYPE,typename ...FILTERT>
typename nxobject_traits<PTYPE>::field_type 
create_field(const PTYPE &parent,const string &name,type_id_t tid, 
             const STYPE shape,FILTERT ...filters)
{
    STYPE cshape(shape.size());
    std::copy(shape.begin(),shape.end(),cshape.begin());
    *cshape.begin() = 1;

    if(tid == type_id_t::UINT8)
        return parent.create_field<uint8>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT8)
        return parent.create_field<int8>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT16)
        return parent.create_field<uint16>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT16)
        return parent.create_field<int16>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT32)
        return parent.create_field<uint32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT32)
        return parent.create_field<int32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT64)
        return parent.create_field<uint64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT64)
        return parent.create_field<int64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT32)
        return parent.create_field<float32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT64)
        return parent.create_field<float64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT128)
        return parent.create_field<float128>(name,shape,cshape,filters...);
    else
        throw type_error(EXCEPTION_RECORD,"Unkown data type!");
}

                  
