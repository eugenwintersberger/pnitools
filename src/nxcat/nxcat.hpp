//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
// Created on: Jun 11,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include <pni/core/types.hpp>
#include <pni/io/nexus.hpp>
#include <pni/io/formatters.hpp>

#include <pni/core/configuration.hpp>

#include "../common/column.hpp"
#include "../common/table.hpp"


using StringList  = std::vector<std::string>;
using SourcesList = std::list<pni::io::nexus::Path>;

//storage type for columns
using ColumnStorage = std::list<pni::core::array>;
using Column        = column<ColumnStorage>;
using Table         = table<Column>;

/*!
\ingroup nxcat_devel
\brief create CLI configuration

Function to create the CLI configuration.
\return configuration object
*/
pni::core::configuration create_configuration();

//------------------------------------------------------------------------------
//!
//! @ingroup nxcat_devel
//! @brief read full table
//!
//! Read all data from a set of nxpath instances and store the result in a table.
//!
//! @param sources list of path object
//! @return table instance
//!
Table  read_table(const SourcesList &sources);

//-----------------------------------------------------------------------------
/*!
\ingroup nxcat_deval
\brief read a single column

Read a single column from a source determined by an nxpath instance.
\param nxpath location of the data
\return column instance
*/
Column read_column(const pni::io::nexus::Path &source_path);

//!
//! @ingroup nxcat_devel
//! @brief read column data from an HDF5 attribute
//!
//! @param attribute reference to an HDF5 attribute
//! @return instance of a Column
//!
Column read_column(const hdf5::attribute::Attribute &attribute);

//!
//! @ingroup nxcat_devel
//! @brief read column data from an HDF5 dataset
//!
//! @param dataset reference to a dataset
//! @return instance of Column holding the data stored in the dataset
//!
Column read_column(const hdf5::node::Dataset &dataset);

//!
//! @ingroup nxcat_devel
//! @brief obtain dimensions from a dataspace
//!
//! This function returns the current dimensions from a given dataspace.
//! In the case of a scalar dataspace the returned dimensions will be
//! {1}.
//!
//! @param dataspace reference to an HDF5 dataspace
//! @return instance of Dimensions
//!
hdf5::Dimensions get_dimensions(const hdf5::dataspace::Dataspace &dataspace);

//!
//! @ingroup nxcat_devel
//! @brief get cell dimensions
//!
//! Cell dimensions are derived from the dimensions of the dataset or
//! attribute. The cell dimensions are basically the objects dimensions
//! stripped of the first. The first dimension will be the number of rows
//! in the resulting column.
//!
//! @param file_dimensions reference to the dimensions on file
//! @return dimensions of the data in a single cell
//!
hdf5::Dimensions get_cell_dimensions(const hdf5::Dimensions &file_dimensions);

//!
//! @ingroup nxcat_devel
//! @brief get pnicore type id from HDF5 datatype
//!
//! This function maps the HDF5 datatype used to create the attribute
//! or dataspace to an pnicore type_id_t which will be later used to
//! to
//!
//! @param datatype reference to an HDF5 datatype
//! @return type_id_t corresponding to the HDF5 type
//!
pni::core::type_id_t get_type_id(const hdf5::datatype::Datatype &datatype);


//
//template<typename NXVAR>
//Column column_from_nexus_object(const NXVAR &o,const string &unit="")
//{
//    Column column;
//    column.name(get_name(o));
//    if(is_attribute(o))
//        column.unit(unit);
//    else
//        column.unit(get_unit(o));
//
//    return column;
//}

//!
//! @brief get source object for table column
//!
//! Retrieve the source object from which to read data for a column. The object
//! must be either a
//!
//! \li HDF5 attribute
//! \li or an HDF5 dataset
//!
//! if the reference object is none of the above an exception will be thrown.
//! The object is referenced by Nexus path which must be precise enough to
//! select a single object below the parent object otherwise an exception
//! will be thrown.
//!
//! \throws std::runtime_error in case of any error
//! \param parent the parent object from which to read the data
//! \param source_path Nexus path determining the object
//! \return a NeXus path object storing a dataset or an attribute
//!
pni::io::nexus::PathObject get_source(const hdf5::node::Group &parent,
                                      const pni::io::nexus::Path &source_path);


//-----------------------------------------------------------------------------
/*!
\ingroup nxcat_devel
\brief create an array from a Nexus object

Create an instance of array from a Nexus object stored in a Nexus variant type.
An nxgroup_error exception is thrown in cases where the stored object is a group
but not an attribute or a field.
In the case of a multidimensional with n dimensions the output array will have
n-1 dimensions with the first dimension of the original object stripped of.


\throws nxgroup_error if object is not an attribute or a field
\tparam NXVAR Nexus variant type
\param o reference to NXOT instance
\return instance of array
*/
//template<typename NXVAR>
//pni::core::array array_from_nexus_object(const NXVAR &o)
//{
//    //get the shape of the object in the file
//    auto file_shape = get_shape<shape_t>(o);
//    shape_t array_shape{1}; //in the worst case we have a scalar object
//                            //than we can use this
//
//    if(is_field(o))
//    {
//        //when the object is a field where we can do partial IO we simply
//        if(file_shape.size() > 1)
//        {
//            //create a new shape with n-1 dimensions
//            array_shape = shape_t(file_shape.size()-1);
//            //copy the original shape by omitting the first dimension
//            std::copy(file_shape.begin()+1,file_shape.end(),array_shape.begin());
//        }
//    }
//
//    return create_array(get_type(o),array_shape);
//}
