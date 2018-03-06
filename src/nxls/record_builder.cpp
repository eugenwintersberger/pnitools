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

#include "record_builder.hpp"
#include <pni/io/nexus.hpp>

RecordBuilder::RecordBuilder(const OutputConfiguration &output_config):
  output_config_(output_config)
{}

const OutputConfiguration &RecordBuilder::output_configuration() const noexcept
{
  return output_config_;
}

size_t RecordBuilder::number_of_columns() const noexcept
{
  if(output_config_.show_long_output())
    return 4;
  else
    return 1;
}

OutputRecord RecordBuilder::operator()(const Metadata::UniquePointer &metadata)
{
  OutputRecord record(number_of_columns());

  record[0] = pni::io::nexus::Path::to_string(metadata->path());
  return record;
}




