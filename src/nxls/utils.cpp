//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "../common/config_utils.hpp"
#include <pni/io/exceptions.hpp>
#include "utils.hpp"

using namespace pni::io;
using namespace pni::core;

nexus::Path get_base_path(const configuration &config)
{
  try
  {
    return nexus::Path::from_string(config.value<string>("nxpath"));
  }
  catch(pni::io::parser_error &error)
  {
    std::cerr<<error<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<"Check if the :// is appended to the filename if you want"
        <<" to show the content from the root group!"<<std::endl;
    std::exit(1);
  }
  catch(...)
  {
    std::cerr<<"Unknown error during path parsing - aborting program!";
    std::cerr<<std::endl;
    std::exit(1);
  }
}

//----------------------------------------------------------------------------
hdf5::file::File get_file(const nexus::Path &path)
{
  if(path.filename().empty())
  {
    std::cerr<<"Please provide a filename!"<<std::endl;
    std::exit(1);
  }

  hdf5::file::File file;
  try
  {
    file = hdf5::file::open(path.filename(),hdf5::file::AccessFlags::READONLY);
  }
  catch(...)
  {
    std::cerr<<"Error opening Nexus file!"<<std::endl;
    std::exit(1);
  }

  return file;
}

//----------------------------------------------------------------------------
nexus::PathObject get_base(const hdf5::file::File &file,
                           const nexus::Path &path)
{
  nexus::PathObjectList objects;

  // check if the path references the root group
  if(path.size()==1 &&  !nexus::has_attribute_section(path))
  {
    return file.root();
  }

  try
  {
    nexus::Path file_root;
    file_root.filename(path.filename());
    file_root.push_back({"/","NXroot"});
    nexus::Path search_path = nexus::make_relative(file_root,path);
    search_path.attribute(path.attribute());
//    if(search_path.size()==1 && search_path.front().first==".")
//      search_path.pop_front();

    std::cout<<"Searching for: "<<search_path<<std::endl;
    objects = nexus::get_objects(file.root(),search_path);

  }
  catch(pni::core::key_error &error)
  {
    std::cerr<<error<<std::endl;
    std::cerr<<"The path entered does not exist!"<<std::endl;
    std::exit(1);
  }
  catch(std::runtime_error &error)
  {
    std::cerr<<error.what()<<std::endl;
    std::exit(1);
  }

  if(objects.size()!=1)
  {
    std::stringstream ss;

    if(objects.size()>1)
      ss<<"The path ["<<path<<"] is not unique - cannot identify base object!";
    else if(objects.size()==0)
      ss<<"Could not find base with ["<<path<<"]!";

    throw std::runtime_error(ss.str());
  }

  return objects.front();
}

std::string shape_to_string(const pni::core::shape_t &shape)
{
    std::stringstream ss;

    if(shape.empty()) return std::string();

    ss<<"(";
    for(auto iter = shape.begin();iter!=shape.end();++iter)
    {
        ss<<*iter;
        if(iter!=shape.end()-1) ss<<",";
    }

    ss<<")";
    return ss.str();

}
