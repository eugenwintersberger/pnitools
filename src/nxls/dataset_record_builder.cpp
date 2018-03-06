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

#include "dataset_record_builder.hpp"
#include "utils.hpp"

using namespace pni::io;

DatasetRecordBuilder::DatasetRecordBuilder(const OutputConfiguration &output_config):
  RecordBuilder(output_config)
{}

DatasetRecordBuilder::~DatasetRecordBuilder()
{}

OutputRecord DatasetRecordBuilder::build_long(const DatasetMetadata &metadata) const
{
  OutputRecord record(number_of_columns());
  record[0] = "FIELD";

  std::stringstream ss;
  ss<<metadata.type_id();
  record[1] = ss.str();
  record[2] = shape_to_string(metadata.shape());
  record[3] = nexus::Path::to_string(adjust_path(metadata.path()));

  return record;
}

OutputRecord DatasetRecordBuilder::build_short(const DatasetMetadata &metadata) const
{
  return OutputRecord{nexus::Path::to_string(adjust_path(metadata.path()))};
}

OutputRecord DatasetRecordBuilder::build(const Metadata::UniquePointer &metadata) const
{
  auto dataset_metadata = dynamic_cast<const DatasetMetadata*>(metadata.get());
  if(output_configuration().show_long_output())
    return build_long(*dataset_metadata);
  else
    return build_short(*dataset_metadata);
}




