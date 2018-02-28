//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: Jun 3, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nexus.hpp>
#include "utils.hpp"

using namespace pni::core;
using namespace pni::io;

//----------------------------------------------------------------------------
configuration create_global_config()
{
    configuration config;

    config.add_option(config_option<bool>("help","h",
                "show help",false));
    config.add_option(config_option<bool>("verbose","v",
                                          "print verbse output",false));
    config.add_option(config_option<char>("begin","b",
                "character indicating start of data"));
    config.add_option(config_option<char>("end","e",
                "character indicating end of data"));
    config.add_option(config_option<char>("separator","s",
                "separator character for data items"));
    config.add_option(config_option<bool>("replace","r",
                "replace data instead of append",false));
    config.add_option(config_option<size_t>("start-index","",
                "start index for replace operation",size_t(0)));
    config.add_argument(config_argument<nexus::Path>("target",1));

    return config;
}

//----------------------------------------------------------------------------
bool show_help(const configuration &config)
{
    if(config.value<bool>("help"))
    {
        std::cerr<<config<<std::endl;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
bool no_target_path(const configuration &config)
{
    if(!config.has_option("target"))
    {
        std::cerr<<"You have to provide a Nexus path to a target object!";
        std::cerr<<std::endl;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
bool get_target_file(const nexus::Path &path,hdf5::file::File &file)
{
    try
    {
        file = nexus::open_file(path.filename(),hdf5::file::AccessFlags::READWRITE);
    }
    catch(...)
    {
        std::cerr<<"Error opening file ["<<path.filename()<<"]!"<<std::endl;
        return false;
    }

    return true;
}

//----------------------------------------------------------------------------
bool get_target_object(const nexus::Path &path,const hdf5::file::File &file,
                       nexus::PathObject &target)
{
    //get the object
    try
    {
    	nexus::PathObjectList targets = nexus::get_objects(file.root(),path);

    	if(targets.size()==0)
    	{
    	  std::cerr<<"Could not find an object matching the path: "<<path<<std::endl;
    	  return false;
    	}
      target = targets.front();
    }
    catch(...)
    {
        std::cerr<<"Error retrieving object ["<<path<<"]!"<<std::endl;
        return false;
    }

    //check if the object is no group
    if(is_group(target))
    {
        std::cerr<<"Target object must be an attribute or a field!"
                 <<std::endl
                 <<"The current target ["<<path<<"] is a group type!"
                 <<std::endl;
        return false;
    }


    return true;
}

pni::core::shape_t get_shape(const pni::io::nexus::PathObject &object)
{
  hdf5::Dimensions dims = get_dimensions(object);

  pni::core::shape_t(dims.begin(),dims.end());
}

hdf5::Dimensions get_dimensions(const pni::io::nexus::PathObject &object)
{
  if(nexus::is_dataset(object))
  {
    hdf5::node::Dataset dataset = object;
    return nexus::get_dimensions(dataset);
  }
  else if(nexus::is_attribute(object))
  {
    hdf5::attribute::Attribute attribute = object;
    return nexus::get_dimensions(attribute);
  }
}

pni::core::type_id_t get_type_id(const pni::io::nexus::PathObject &object)
{
  if(nexus::is_dataset(object))
  {
    hdf5::node::Dataset dataset = object;
    return nexus::get_type_id(dataset);
  }
  else if(nexus::is_attribute(object))
  {
    hdf5::attribute::Attribute attribute = object;
    return nexus::get_type_id(attribute);
  }
}
