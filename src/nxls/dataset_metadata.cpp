//
// (c) Copyright 2018 DESY
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
// Created on: Feb 28, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "dataset_metadata.hpp"

using namespace pni::core;
using namespace pni::io;

namespace {

shape_t dimensions_to_shape(const hdf5::Dimensions &dims)
{
  return shape_t(dims.begin(),dims.end());
}

}

DatasetMetadata::DatasetMetadata(const hdf5::node::Dataset &dataset):
DataMetadata(nexus::get_path(dataset),
             nexus::get_type_id(dataset),
             dimensions_to_shape(nexus::get_dimensions(dataset)))
{}

Metadata::Type DatasetMetadata::type() const
{
  return Metadata::Type::DATASET;
}



