//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 14, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <numeric>
#include "integrate.hpp"


integrate::integrate():image_op_base(image_type::create(shape_t{{1}})) {}

//-----------------------------------------------------------------------------
void integrate::execute(const image_type &image)
{
    typedef image_type::value_type value_type;
    result()[0] = std::accumulate(image.begin(),image.end(),value_type(0));
}
