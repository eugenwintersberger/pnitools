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
// Created on: Mar 6, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "link_record_builder.hpp"

using namespace pni::io;

OutputRecord LinkRecordBuilder::build_long(const LinkMetadata &metadata) const
{
  OutputRecord record(number_of_columns());

  std::stringstream ss;

  record[0] = "LINK";

  ss<<metadata.link_type();
  record[2] = ss.str();

  ss.str(std::string());
  ss.clear();
  ss<<adjust_path(metadata.path())<<" -> ";
  if(metadata.link_type() == hdf5::node::LinkType::SOFT)
    ss<<metadata.link_target().object_path();
  else if(metadata.link_type() == hdf5::node::LinkType::EXTERNAL)
    ss<<metadata.link_target().file_path().string()<<":/"<<metadata.link_target().object_path();

  record[3] = ss.str();

  return record;
}

OutputRecord LinkRecordBuilder::build_short(const LinkMetadata &metadata) const
{
  OutputRecord record(number_of_columns());

  record[0] = nexus::Path::to_string(adjust_path(metadata.path()));
  return record;
}


LinkRecordBuilder::LinkRecordBuilder(const OutputConfiguration &output_config):
RecordBuilder(output_config)
{}

LinkRecordBuilder::~LinkRecordBuilder()
{}

OutputRecord LinkRecordBuilder::build(const Metadata::UniquePointer &metadata) const
{
  auto link_metadata = dynamic_cast<LinkMetadata*>(metadata.get());
  if(output_configuration().show_long_output())
    return build_long(*link_metadata);
  else
    return build_short(*link_metadata);

}



