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
// ===========================================================================
// Created on: Oct 17, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include "xml2nx.hpp"
#include <pni/io/exceptions.hpp>
#include "../common/config_utils.hpp"

static const std::string program_name = "xml2nx";
static const std::string help_header =
"Program usage:\n  xml2nx [OPTIONS] INPUT FILES";

using namespace pni::core;
using namespace pni::io;

std::string get_data_from_stream(std::istream &stream)
{
  std::string output;
  while(!stream.eof())
  {
    std::string line_buffer;
    std::getline(stream,line_buffer);
    output+=line_buffer;
  }
  return output;
}

int main(int argc,char **argv)
{
  configuration conf = create_config();

  if(argc<2)
  {
    std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
    std::cerr<<"Use xml2nx -h for help  ..."<<std::endl;
    return 1;
  }

  //--------- setup CLI configuration ---------------------------------------
  try
  {
    if(parse_cli_opts(argc,argv,program_name,conf))
      return 1;

    if(check_help_request(conf,help_header))
      return 1;
  }
  catch(pni::core::cli_option_error &error)
  {
    std::cerr<<"Error during parsing command line options and arguments!";
    std::cerr<<std::endl;
    std::cerr<<error<<std::endl;
    return 1;
  }

  //
  // create the nexus path from user input
  //
  nexus::Path path;
  try
  {
    path = nexus::Path::from_string(conf.value<std::string>("parent"));
  }
  catch(const pni::core::cli_option_error &error)
  {
    std::cerr<<"Error parsing target path!"<<std::endl;
    std::cerr<<error.description()<<std::endl;
    return 1;
  }
  catch(const parser_error &error)
  {
    std::cerr<<"Error parsing target path: "<<error.description()<<std::endl;
    return 1;
  }

  //
  // open the file
  //
  hdf5::file::File nexus_file;
  try
  {
    nexus_file = open_nexus_file(path,conf.value<bool>("overwrite"));
  }
  catch(const cli_error &error)
  {
    std::cerr<<"Error opening/creating file: "<<path.filename()<<std::endl;
    std::cerr<<error.description()<<std::endl;
    return 1;
  }
  catch(const std::runtime_error &error)
  {
    std::cerr<<"Error opening/creating file: "<<path.filename()<<std::endl;
    std::cerr<<error.what()<<std::endl;
    return 1;
  }
  catch(...)
  {
    std::cerr<<"Unkonw error opening/creating file: "<<path.filename()<<std::endl;
    return 1;
  }

  //
  // get the parent group
  //
  hdf5::node::Group parent_group = nexus_file.root();
  if(path.size()!=0)
  {
    nexus::PathObjectList objects = nexus::get_objects(parent_group,path);
    if(objects.size()==1 && nexus::is_group(objects.front()))
    {
      parent_group = objects.front();
    }
  }

  //
  // create structure fom XML
  //
  try
  {

    if(conf.has_option("input-file"))
    {
      //read XML data from an input file
      nexus::xml::create_from_file(parent_group,conf.value<std::string>("input-file"));
    }
    else
    {
      //read data from input stream
      std::string xml_data = get_data_from_stream(std::cin);
      nexus::xml::create_from_string(parent_group,xml_data);
    }


    parent_group.close();
    nexus_file.close();
  }
  catch(const pni::core::cli_option_error &error)
  {
    std::cerr<<error<<std::endl;
    return 1;
  }
  catch(pni::io::parser_error &error)
  {
    std::cerr<<error<<std::endl;
    return 1;
  }
  catch(file_error &error)
  {
    std::cerr<<error<<std::endl;
    return 1;
  }
  catch(...)
  {
    std::cerr<<"Unkown error!"<<std::endl;
    return 1;
  }
    return 0;
}
