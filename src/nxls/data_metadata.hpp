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

#include "metadata.hpp"
#include <pni/core/types.hpp>

class DataMetadata : public Metadata
{
  private:
    pni::core::type_id_t type_id_;
    pni::core::shape_t   shape_;
  public:
    DataMetadata(const pni::io::nexus::Path &path,
                 pni::core::type_id_t tid,
                 pni::core::shape_t shape);

    pni::core::type_id_t type_id() const noexcept;
    pni::core::shape_t   shape() const noexcept;
};
