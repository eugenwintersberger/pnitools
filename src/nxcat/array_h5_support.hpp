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
// Created on: March 21, 2018
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus.hpp>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>

namespace hdf5 {
namespace datatype {

template<> class TypeTrait<pni::core::array>
{
  public:
    using TypeClass = Datatype;

    static TypeClass create(const pni::core::array &array = pni::core::array())
    {
      return pni::io::nexus::DatatypeFactory::create(array.type_id());
    }

};

} // namespace datatype
} // namespace hdf5

namespace hdf5 {
namespace dataspace {

template<> class TypeTrait<pni::core::array>
{
  public:
    using DataspaceType = Dataspace;

    static DataspaceType create(const pni::core::array &array)
    {
      if(array.size() == 1)
      {
        return Scalar();
      }
      else
      {
        auto current_dimensions = array.shape<hdf5::Dimensions>();
        return Simple(current_dimensions);
      }
    }

    static void *ptr(pni::core::array &array)
    {
      return array.data();
    }

    static const void *ptr(const pni::core::array &array)
    {
      return array.data();
    }
};

} // namespace dataspace
} // namespace hdf5
