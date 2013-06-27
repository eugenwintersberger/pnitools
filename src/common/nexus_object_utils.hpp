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

using namespace pni::core;
using namespace pni::io::nx;

/*!
\ingroup common_devel
\brief get the object class

Returns the class of an object by returning the value of the NX_class attribute
of an object. Currently this will only return a value if the object is a group
type. However, due to the generallity of the code this could also be a field or
any other type that can hold attributes.
If the object has no attribute NX_class an empty string will be returned.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\return value of NX_class attribute
*/
template<typename OTYPE> string get_class(const OTYPE &o)
{
    string value;
    if(o.has_attr("NX_class"))
        o.attr("NX_class").read(value);

    return value;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief set object class

Set the NX_class attribute of an object.  Naturally this function should only be
used with groups.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\param s object class
*/
template<typename OTYPE> void set_class(const OTYPE &o,const string &s)
{
    o.template attr<string>("NX_class",true).write(s);
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief check object class

Returns true if an object is of a particular class. 
\tparam OTYPE object type
\param o reference to instance of OTYPE
\param type type string 
\return true if object class and type are equal
*/
template<typename OTYPE> bool is_class(const OTYPE &o,const string &type)
{
    return get_class(o)==type;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief true if object is group

Return true if an instance of an object is a group type.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\return true if o is a group 
*/
template<typename OTYPE> bool is_group(const OTYPE &o)
{
    return o.object_type()==nxobject_type::NXGROUP;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief true if object is a field

Return true if an instance of an object is a field object.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\return true of o is a field
*/
template<typename OTYPE> bool is_field(const OTYPE &o)
{
    return o.object_type() == nxobject_type::NXFIELD;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get unit of a field

Returns the unit of a Nexus field. If the Nexus field has no unit attached to it
an empty string is returned. 
\tparam FTYPE field type
\param f instance of FTYPE
\return string with the unit of the field
*/
template<typename FTYPE>  string get_unit(const FTYPE &f)
{
    string buffer;
    if(f.has_attr("units"))
        f.attr("units").read(buffer);

    return buffer;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief set the unit of an object

Sets the unit of a Nexus object. 
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\param s unit string
*/
template<typename OTYPE> void set_unit(const OTYPE &o,const string &u)
{
    o.template attr<string>("units",true).write(u);
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief return status

Return true if a Nexus object is valid. 
\tparam OTPYE object type
\param o reference to the object
\return true if the object is valid
*/
template<typename OTYPE> bool is_valid(const OTYPE &o)
{
    return o.is_valid();
}
