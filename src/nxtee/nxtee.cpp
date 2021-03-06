//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 18,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <iostream>
#include <fstream>

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>

#include <pni/io/nexus.hpp>

#include "operation.hpp"
#include "utils.hpp"

using namespace pni::io;
using namespace pni::core;

static const std::string program_name = "nxtee";
static const std::string help_header =
"Program usage:\n  nxtee NEXUSPATH";


int main(int argc,char **argv)
{
  //-------------------------------------------------------------------------
  //before anything else we check if the user has provided enough command line
  //arguments
  if(argc<2)
  {
    std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
    std::cerr<<"Use nxtee -h for help  ..."<<std::endl;
    return 1;
  }

  configuration config = create_global_config();
  parse(config,cliargs2vector(argc,argv));

  //------------------------------------------------------------------------
  // check command line options
  //------------------------------------------------------------------------
  if(show_help(config)) return 1;
  if(no_target_path(config)) return 1;

  //------------------------------------------------------------------------
  // retrieve the target object
  //------------------------------------------------------------------------

  //retrieve the path to the target
  auto target_path = config.value<nexus::Path>("target");

  //get the file
  hdf5::file::File file;
  if(!get_target_file(target_path,file)) return 1;

  //get the object in the file
  if(config.value<bool>("verbose"))
  {
    std::cout<<"Looking for target: "<<target_path<<std::endl;
  }
  nexus::PathObject target;
  if(!get_target_object(target_path,file,target)) return 1;

  if(config.value<bool>("verbose"))
  {
    std::cout<<"Got target: ";
    switch(target.type())
    {
      case nexus::PathObject::Type::ATTRIBUTE:
      {
        hdf5::attribute::Attribute attribute = target;
        std::cout<<nexus::get_path(attribute);
      }
      break;
      case nexus::PathObject::Type::DATASET:
      {
        hdf5::node::Dataset dataset = target;
        std::cout<<nexus::get_path(dataset);
      }
    }
  }


  //------------------------------------------------------------------------
  // perform operation - currently append is implemented
  //------------------------------------------------------------------------
  if(config.value<bool>("replace"))
  {
    replace(target,config.value<size_t>("start-index"));
  }
  else
  {
    if(is_attribute(target))
    {
      std::cerr<<"Cannot append data to an attribute - abort!"<<std::endl;
      return 1;
    }

    try
    {
      append(target);
    }
    catch(range_error &error)
    {
      std::cerr<<error<<std::endl;
      return 1;
    }
  }

  //in case of success we return 0
  return 0;
}
