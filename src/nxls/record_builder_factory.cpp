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

#include "record_builder_factory.hpp"
#include "attribute_record_builder.hpp"
#include "link_record_builder.hpp"
#include "dataset_record_builder.hpp"
#include "group_record_builder.hpp"


RecordBuilderFactory::RecordBuilderFactory(const OutputConfiguration &output_config):
  output_config_(output_config)
{}

RecordBuilder::Pointer RecordBuilderFactory::create(const Metadata::UniquePointer &metadata) const
{
  switch(metadata->type())
  {
    case Metadata::Type::ATTRIBUTE:
      return RecordBuilder::Pointer(new AttributeRecordBuilder(output_config_));
    case Metadata::Type::DATASET:
      return RecordBuilder::Pointer(new DatasetRecordBuilder(output_config_));
    case Metadata::Type::GROUP:
      return RecordBuilder::Pointer(new GroupRecordBuilder(output_config_));
    case Metadata::Type::LINK:
      return RecordBuilder::Pointer(new LinkRecordBuilder(output_config_));
  }
}



