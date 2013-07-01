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
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>

using namespace boost::mpl;

template<typename OTYPE> 
class is_field_visitor : public boost::static_visitor<bool>
{
    public:
        DEFINE_NXGROUP(OTYPE) group_type;
        DEFINE_NXFIELD(OTYPE) field_type;
        DEFINE_NXATTRIBUTE(OTYPE) attribute_type;
        
        bool operator()(const group_type &g) const
        {
            return false;
        }

        bool operator()(const field_type &f) const
        {
            return true;
        }

        bool operator()(const attribute_type &a) const
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
template<typename VTYPE> bool is_field(const VTYPE &o)
{
    /*
    typedef typename VTYPE::types vtypes;
    typedef typename begin<vtypes>::type   viter;
    return boost::apply_visitor(is_field_visitor<typename deref<viter>::type>(),o);
    */
    return boost::apply_visitor(is_field_visitor<typename
            nxvariant_object_type<VTYPE>::group_type>(),o);
}

