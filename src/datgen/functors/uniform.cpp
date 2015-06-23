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

#include "uniform.hpp"

using namespace pni::core;

uniform::uniform(float64 lower_bound,float64 upper_bound):
    functor(),
    _generator(std::random_device()()),
    _distribution(distribution_type(lower_bound,upper_bound))
{
    if(upper_bound < lower_bound)
        throw range_error(EXCEPTION_RECORD,
                "Upper bound of uniform random generator is smaller than"
                " lower bound!");
}

//----------------------------------------------------------------------------
float64 uniform::operator()(float64 x) const
{
    return _distribution(_generator);
}

//----------------------------------------------------------------------------
std::ostream &uniform::to_stream(std::ostream &stream) const
{
    return stream;
}
