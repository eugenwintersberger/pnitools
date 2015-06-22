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
// Created on: Jun 9, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "executor.hpp"

using namespace pni::core;

executor::executor():
    _functors()
{}

//----------------------------------------------------------------------------
executor::executor(functor_vector &&functors):
    _functors(std::move(functors))
{}

//----------------------------------------------------------------------------
float64 executor::operator()(float64 x) const
{
    float64 result = 0.0;
    for(auto & f: _functors)
        result += (*f)(x);

    return result;
}
