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
 * Created on: Jun 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxvariant_traits.hpp"

using namespace boost::mpl;

template<typename VTYPE> 
class is_field_visitor : public boost::static_visitor<bool>
{
    public:
        typedef typename nxvariant_member_type<VTYPE,0>::type first_type;
        typedef bool result_type;   
        DEFINE_NXGROUP(first_type) group_type;
        DEFINE_NXFIELD(first_type) field_type;
        DEFINE_NXATTRIBUTE(first_type) attribute_type;
        
        result_type operator()(const group_type &g) const
        {
            return false;
        }

        result_type operator()(const field_type &f) const
        {
            return true;
        }

        result_type operator()(const attribute_type &a) const
        {
            return false;
        }
};

/*!
\ingroup common_devel
\brief check if field

\tparam VTYPE Nexus object variant type
\param o instance of VTYPE
\return true if the object is a field
*/
template<typename VTYPE> 
typename is_field_visitor<VTYPE>::result_type is_field(const VTYPE &o)
{
    return boost::apply_visitor(is_field_visitor<VTYPE>(),o);
}

