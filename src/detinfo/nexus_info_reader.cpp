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
// Created on: Oct 7,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include "nexus_info_reader.hpp"
#include "../common/file.hpp"

//----------------------------------------------------------------------------
detector_layout nexus_info_reader::get_detector_layout(const hdf5::node::Group &detector_group)
{
    std::string layout;
    hdf5::node::Dataset(detector_group.nodes["layout"]).read(layout);
    layout = trim(layout);

    return layout_from_string(layout);
}

detector_info_list nexus_info_reader::operator()(const file &f) const
{
  detector_info_list list;

  //select all detecotor instances
  hdf5::file::File input = hdf5::file::open(f.path(),hdf5::file::AccessFlags::READONLY);

  detector_list detectors = nexus::search(input.root(),nexus::IsDetector(),true);

  for(auto detector: detectors)
    list.push_back(info_from_nxdetector(detector));

  return list;
}

//----------------------------------------------------------------------------
detector_info nexus_info_reader::info_from_nxdetector(const hdf5::node::Group &d)
{
  //obtain the link to the detector data
  hdf5::node::Link link = d.links["data"];

  //retrieve the layout of the detector group
  detector_layout layout = get_detector_layout(d);

  //if the link is not resolvable we store only the link information
  if(!link.is_resolvable())
  {
    std::stringstream ss;
    ss<<link.target().object_path();
    return detector_info(link.target().file_path().string(),layout,ss.str());
  }

  //resolve the link to a dataspace
  hdf5::node::Dataset data(*link);
  std::string path = nexus::Path::to_string(nexus::get_path(data));

  //get the shape of the detector
  hdf5::dataspace::Dataspace space = data.dataspace();
  hdf5::Dimensions dims{1};
  if(space.type() == hdf5::dataspace::Type::SIMPLE)
    dims = hdf5::dataspace::Simple(space).current_dimensions();
    
  //create the infor object
  shape_t shape(dims.begin(),dims.end());
  type_id_t tid = nexus::get_type_id(data);
  switch(get_detector_layout(d))
  {
    case detector_layout::POINT:
      return detector_info(shape_t{},tid,path,shape[0],layout);
    case detector_layout::LINEAR:
      return detector_info(shape,tid,path,shape[0],layout);
    case detector_layout::AREA:
      return detector_info(shape_t{shape[1],shape[2]},
                           tid,path,shape[0],layout);
    default:
      throw type_error(EXCEPTION_RECORD,"Unknown detector layout!");
  }
}
