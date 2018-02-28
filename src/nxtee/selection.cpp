//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: Jun 3, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "selection.hpp"
#include "utils.hpp"

 hdf5::dataspace::Hyperslab Selection::create(const pni::io::nexus::PathObject &object)
 {
   //
   // obtain the current dimensions of the target object
   //
   hdf5::Dimensions dims = get_dimensions(object);

   //
   // create the block container
   //
   hdf5::Dimensions block(dims);
   block.front() = 1;

   //
   // create the offset container
   //
   hdf5::Dimensions offset(dims.size());
   std::fill(offset.begin(),offset.end(),0);

   offset.front() = dims.front(); // set the offset
   //if(offset.front()!=0)
   //  offset.front() = offset.front()-1;

   return hdf5::dataspace::Hyperslab(offset,block);
 }

