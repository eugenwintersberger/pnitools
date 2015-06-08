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
// ===========================================================================
// Created on: 8 May, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "grid_generator.hpp"

using namespace pni::core;

grid_generator::grid_generator():
    _value(0),
    _delta(0)
{}

//----------------------------------------------------------------------------
grid_generator::grid_generator(float64 start, float64 delta):
    _value(start),
    _delta(delta)
{}

//----------------------------------------------------------------------------
void grid_generator::start(float64 start)
{
    _value = start;
}

//----------------------------------------------------------------------------
void grid_generator::delta(float64 delta)
{
    _delta = delta;
}

//----------------------------------------------------------------------------
float64 grid_generator::operator()()
{
    float64 temp = _value;
    _value += _delta;

    return temp;
}

