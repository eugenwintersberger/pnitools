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
 * Created on: Jun 7, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxobject_traits.hpp"

#include <boost/variant.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

using namespace pni::io::nx;
using namespace boost;

/*!
\ingroup common_devel
\brief nexus object variants

This traits provides different boost::variant types for data IO. 
\tparam OTYPE object type
*/
template<typename OTYPE> struct nxvariant_traits
{
    /*!
    \brief general object types

    A variant holding all types interesting for an application using Nexus.
    */
    typedef boost::variant<typename nxobject_traits<OTYPE>::group_type,
                           typename nxobject_traits<OTYPE>::field_type,
                           typename nxobject_traits<OTYPE>::attribute_type>
                               object_types;

    /*!
    \brief IO types

    A variant holding all nexus types that can do data IO.
    */
    typedef boost::variant<typename nxobject_traits<OTYPE>::field_type,
                           typename nxobject_traits<OTYPE>::attribute_type>
                               io_types;
};


/*!
\ingroup common_devel
\brief get group type

Returns the group type from a object_types variant. In some cases we need to
obtain the differnt types form the variants.

\tparam VTYPE variant type
*/
template<typename VTYPE> struct nxvariant_object_types
{
    typedef typename mpl::at<typename VTYPE::types,mpl::int_<0> >::type group_type; //!< the group type
    typedef typename mpl::at<typename VTYPE::types,mpl::int_<1> >::type field_type;
    typedef typename mpl::at<typename VTYPE::types,mpl::int_<2> >::type attribute_type;
};

template<typename VTYPE> struct nxvariant_io_types
{
    typedef typename mpl::at<typename VTYPE::types,mpl::int_<0> >::type field_type;
    typedef typename mpl::at<typename VTYPE::types,mpl::int_<1> >::type attribute_type;
};


