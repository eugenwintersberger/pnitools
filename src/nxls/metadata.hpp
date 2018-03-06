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
// Created on: Feb 28, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <pni/io/nexus.hpp>

//!
//! @ingroup nxls_devel
//! @brief abstract metadata interface
//!
//! This class is the base for all metadata classes.
class Metadata
{
  private:
    pni::io::nexus::Path nexus_path_;
  public:
    enum class Type
    {
      ATTRIBUTE,DATASET,LINK,GROUP
    };

    using UniquePointer = std::shared_ptr<Metadata>;
    explicit Metadata(const pni::io::nexus::Path &path);
    virtual ~Metadata();

    pni::io::nexus::Path path() const;
    virtual Type type() const = 0;
};

//!
//! @ingroup nxls_devel
//! @brief list with metadata pointers
//!
class MetadataList : public std::list<Metadata::UniquePointer>
{
  public:
    using std::list<Metadata::UniquePointer>::list;
};
