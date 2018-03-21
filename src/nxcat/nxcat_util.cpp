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
// ============================================================================
// Created on: Jun 11,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "nxcat.hpp"

using namespace pni::io;

configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_argument(config_argument<StringList>("source",-1));
    config.add_option(config_option<bool>("header","",
                      "show header with units",false));
    config.add_option(config_option<size_t>("start","s",
                "first row in output",size_t(0)));
    config.add_option(config_option<size_t>("end","e",
                "last row in output",size_t(0)));
    return config;
}

//-----------------------------------------------------------------------------
Table read_table(const SourcesList &sources)
{
    Table t;
    for(auto source: sources)
        t.push_back(read_column(source));

    return t;
}



hdf5::Dimensions get_dimensions(const hdf5::dataspace::Dataspace &dataspace)
{
  if(dataspace.type() == hdf5::dataspace::Type::SCALAR)
    return hdf5::Dimensions{1};
  else
    return hdf5::dataspace::Simple(dataspace).current_dimensions();
}

hdf5::Dimensions get_cell_dimensions(const hdf5::Dimensions &file_dimensions)
{
  //construct the shape of a single cell entry - this is typically
  //an array whose original rank is reduced by 1 dimension
  return file_dimensions.size() >1 ?
      hdf5::Dimensions(++file_dimensions.begin(),file_dimensions.end()):
      hdf5::Dimensions{1} ;
}


//-----------------------------------------------------------------------------
Column read_column(const nexus::Path &source_path)
{
  //open file in read only mode - the file must obviously exist
  hdf5::file::File file = nexus::open_file(source_path.filename(),
                                           hdf5::file::AccessFlags::READONLY);
  hdf5::node::Group root = file.root();

  //have to retrieve the object from the file
  nexus::PathObjectList objects = nexus::get_objects(root,source_path);

  //check if the object is empty - throw an exception in this case
  if(objects.size()!=1)
  {
    std::stringstream ss;
    if(objects.size() == 0)
    {
      ss<<"There is no object referenced by ["<<nexus::Path::to_string(source_path)<<"]!";
    }
    else
    {
      ss<<"The path ["<<nexus::Path::to_string(source_path)<<"] references more than one"
        <<" object!";
    }
    throw std::runtime_error(ss.str());
  }
  nexus::PathObject object = objects.front();

  if(object.type() == nexus::PathObject::Type::ATTRIBUTE)
  {
    hdf5::attribute::Attribute attribute = object;
    return read_column(attribute);
  }
  else if(object.type() == nexus::PathObject::Type::DATASET)
  {
    hdf5::node::Dataset dataset = object;
    return read_column(dataset);
  }
  else
  {
    std::stringstream ss;
    ss<<"The object referenced by ["<<nexus::Path::to_string(source_path)+"] is neither a "
      <<" dataset or attribute!";
    throw std::runtime_error(ss.str());
  }


//  //get the shape fo the data on the file
//  hdf5::Dimensions file_shape = get_shape(object);
//  hdf5::Dimensions data_shape = get_data_shape(file_shape);
//
//  //create the data array
//  pni::core::array data = pni::core::make_array(get_type(object),data_shape);
//
//
//  //create a selection in order to read data from the file
//  hdf5::dataspace::Hyperslab selection = create_selection(file_shape,data_shape);
//
//  for(size_t i=0;i<file_shape[0];++i)
//  {
//    selection[0] = slice(i);
//    read(object,data,selection);
//    column.push_back(data);
//  }
//
//    return column;
}


