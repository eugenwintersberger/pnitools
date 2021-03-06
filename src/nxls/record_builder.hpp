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

#include "metadata.hpp"
#include "output_record.hpp"
#include "output_configuration.hpp"

//!
//! @brief base class for all record builders
//!
class RecordBuilder
{
  private:
    OutputConfiguration output_config_;
  protected:
    pni::io::nexus::Path adjust_path(const pni::io::nexus::Path &orig_path) const;
  public:
    using Pointer = std::shared_ptr<RecordBuilder>;
    RecordBuilder(const OutputConfiguration &output_config);
    virtual ~RecordBuilder() {}

    const OutputConfiguration &output_configuration() const noexcept;
    size_t number_of_columns() const noexcept;

    virtual OutputRecord build(const Metadata::UniquePointer &metadata) const;


    OutputRecord operator()(const Metadata::UniquePointer &metadata) const;

};

