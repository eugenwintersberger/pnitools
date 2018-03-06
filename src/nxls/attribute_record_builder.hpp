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
#pragma once

#include "output_configuration.hpp"
#include "output_record.hpp"
#include "metadata.hpp"
#include "record_builder.hpp"
#include "attribute_metadata.hpp"


class AttributeRecordBuilder : public RecordBuilder
{
  private:
    OutputRecord build_long(const AttributeMetadata &metadata) const;
    OutputRecord build_short(const AttributeMetadata &metadata) const;
  public:
    AttributeRecordBuilder(const OutputConfiguration &output_config);
    virtual ~AttributeRecordBuilder();

    virtual OutputRecord build(const Metadata::UniquePointer &metadata) const;
};


