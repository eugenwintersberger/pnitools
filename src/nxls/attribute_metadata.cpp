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

#include "attribute_metadata.hpp"

using namespace pni::io;
using namespace pni::core;

namespace {

shape_t dimensions_to_shape(const hdf5::Dimensions &dims)
{
  return shape_t(dims.begin(),dims.end());
}

}

AttributeMetadata::AttributeMetadata(const hdf5::attribute::Attribute &attribute):
  DataMetadata(nexus::get_path(attribute),
               nexus::get_type_id(attribute),
               dimensions_to_shape(nexus::get_dimensions(attribute)))
{}

Metadata::Type AttributeMetadata::type() const
{
  return Metadata::Type::ATTRIBUTE;
}




