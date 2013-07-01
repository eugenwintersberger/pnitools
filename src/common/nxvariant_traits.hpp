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

/*!
\ingroup common_devel
\brief nexus object variants

This traits provides different boost::variant types for data IO. The template
cna be instantiated from any nexus low level type. Internally nxobject_traits is
used to obtain all related nexus objects.  

All operations on such a type should be done by visitors (see the BOOST::variant
documentation for details about that. 

\tparam OTYPE object type
*/
template<typename OTYPE> struct nxvariant_traits
{
    typedef typename nxobject_traits<OTYPE>::group_type group_type;
    typedef typename nxobject_traits<OTYPE>::field_type field_type;
    typedef typename nxobject_traits<OTYPE>::attribute_type attribute_type;
    /*!
    \brief general object types

    A variant holding all types interesting for an application using Nexus.
    */
    typedef boost::variant<group_type,field_type,attribute_type> object_types;

    /*!
    \brief child types

    This variant collates all types that are possible child types of a group or
    file. 
    */
    typedef boost::variant<group_type,field_type> child_types;

    /*!
    \brief IO types

    A variant holding all nexus types that can do data IO.
    */
    typedef boost::variant<field_type,attribute_type> io_types;
};

template<typename VTYPE,int i> struct nxvariant_member_type
{
    typedef typename boost::mpl::at<typename VTYPE::types,boost::mpl::int_<0> >::type type; 
};

