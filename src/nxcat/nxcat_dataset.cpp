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
// Created on: March 20, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "nxcat.hpp"
//#include "array_h5_support.hpp"

using namespace pni::io;

hdf5::dataspace::Hyperslab create_selection(const hdf5::Dimensions &file_dimensions,
                                            const hdf5::Dimensions &data_dimensions)
{
  hdf5::Dimensions offset(file_dimensions.size(),0);
  hdf5::Dimensions block(file_dimensions.size(),1);

  std::copy(data_dimensions.begin(),data_dimensions.end(),++block.begin());

  return hdf5::dataspace::Hyperslab(offset,block);
}

Column read_column(const hdf5::node::Dataset &dataset)
{
  //
  // create the initial column instance
  //
  Column column;
  column.name(dataset.link().path().name());
  if(dataset.attributes.exists("units"))
  {
    std::string units;
    dataset.attributes["units"].read(units);
  }

  hdf5::Dimensions file_dimensions = get_dimensions(dataset.dataspace());
  hdf5::Dimensions data_dimensions = get_cell_dimensions(file_dimensions);
  pni::core::type_id_t tid         = nexus::get_type_id(dataset);
  hdf5::dataspace::Hyperslab selection = create_selection(file_dimensions,data_dimensions);

  pni::core::array cell_array = pni::core::make_array(tid,data_dimensions);

  for(size_t column_index=0;column_index<file_dimensions[0];++column_index)
  {
    selection.offset(1,column_index);
    dataset.read(cell_array,selection);
    column.push_back(cell_array);
  }
  return column;
}



