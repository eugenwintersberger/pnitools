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

#include "group_record_builder.hpp"
using namespace pni::io;

GroupRecordBuilder::GroupRecordBuilder(const OutputConfiguration &output_config):
RecordBuilder(output_config)
{}

GroupRecordBuilder::~GroupRecordBuilder()
{}

OutputRecord GroupRecordBuilder::build_long(const GroupMetadata &metadata) const
{
  OutputRecord record(number_of_columns());
  record[0] = "GROUP";
  record[3] = nexus::Path::to_string(adjust_path(metadata.path()));
  return record;
}

OutputRecord GroupRecordBuilder::build_short(const GroupMetadata &metadata) const
{
  return OutputRecord{nexus::Path::to_string(adjust_path(metadata.path()))};
}

OutputRecord GroupRecordBuilder::build(const Metadata::UniquePointer &metadata) const
{
  auto group_metadata = dynamic_cast<const GroupMetadata*>(metadata.get());
  if(output_configuration().show_long_output())
    return build_long(*group_metadata);
  else
    return build_short(*group_metadata);
}




