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
// Created on: March 21, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "nxcat.hpp"

using namespace pni::io;

Column read_column(const hdf5::attribute::Attribute &attribute)
{
  Column column;
  column.name(attribute.name());

  hdf5::Dimensions file_dimensions = get_dimensions(attribute.dataspace());
  hdf5::Dimensions data_dimensions = get_cell_dimensions(file_dimensions);
  pni::core::type_id_t tid         = nexus::get_type_id(attribute);

  //TODO: need to ad some code how to fill in the data from an attribute
  //      which cannot be read by a selection

  return column;

}




