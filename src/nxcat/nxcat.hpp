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
 * Created on: Jun 11,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include<iostream>
#include<fstream>
#include<list>
#include<vector>

#include<pni/core/types.hpp>
#include<pni/io/nx/nx.hpp>
#include<pni/io/nx/nxpath.hpp>
#include<pni/io/nx/nxobject_type.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include "../common/field_io.hpp"

#include "../common/column.hpp"
#include "../common/table.hpp"
#include "../common/array_utils.hpp"

#include <pni/io/nx/nxvariant.hpp>

using namespace pni::core;
using namespace pni::io::nx;

typedef std::vector<string> string_list;
typedef std::list<nxpath> sources_list;

//storage type for columns
typedef std::list<array> column_storage_t;
typedef column<column_storage_t> column_t;
typedef table<column_t> table_t;

/*!
\ingroup nxcat_devel
\brief create CLI configuration

Function to create the CLI configuration.
\return configuration object
*/
configuration create_configuration();

//-----------------------------------------------------------------------------
/*!
\ingroup nxcat_deval
\brief read a single column

Read a single column from a source determined by an nxpath instance.
\param nxpath location of the data
\return column instance 
*/
column_t read_column(const nxpath &source_path);

//------------------------------------------------------------------------------
/*!
\ingroup nxcat_devel
\brief read full table

Read all data from a set of nxpath instances and store the result in a table. 
\param sources list of path object
\return table instance
*/
table_t  read_table(const sources_list &sources);

//-----------------------------------------------------------------------------
/*!
\ingroup nxcat_devel
\brief column from nexus object

Create a column from a Nexus object (either a field or an attribute). 
This Nexus object is stored in a variant types as defined by nxvariant_types.
As attributes do not provide a unit one can use the unit argument to this
function. By default the unit will be taken from the field. However, if this
fails the unit will be taken from the argument.

\tparam NXVAR nexus object variant type
\param o instance of NXVAR
\param unit string with unit values
\return instance of column_t
*/
template<typename NXVAR> 
column_t column_from_nexus_object(const NXVAR &o,const string &unit="")
{
    column_t column;
    column.name(get_name(o));
    if(is_attribute(o))
        column.unit(unit);
    else
        column.unit(get_unit(o));

    return column;
}

//-----------------------------------------------------------------------------
/*!
\ingroup nxcat_devel
\brief create an array from a Nexus object

Create an instance of array from a Nexus object stored in a Nexus variant type. 
An nxgroup_error exception is thrown in cases where the stored object is a group
but not an attribute or a field.

\throws nxgroup_error if object is not an attribute or a field
\tparam NXVAR Nexus variant type
\param o reference to NXOT instance
\return instance of array
*/
template<typename NXVAR> 
array array_from_nexus_object(const NXVAR &o)
{
    //get the shape of the object in the file
    auto file_shape = get_shape<shape_t>(o);
    shape_t array_shape{1};

    if(file_shape.size() != 1)
    {
        array_shape = shape_t(file_shape.size()-1);
        std::copy(file_shape.begin()+1,file_shape.end(),array_shape.begin());
    }
    return create_array(get_type(o),array_shape);
}
