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

#include <cstdlib>
#include "gauss.hpp"

using namespace pni::core;

const float64 PI = std::acos(-1);

gauss::gauss(float64 sigma,float64 mu,float64 amplitude):
    functor(),
    _sigma(sigma),
    _mu(mu),
    _amp(amplitude)
{}

//----------------------------------------------------------------------------
float64 gauss::operator()(float64 x) const
{   
    float64 e = std::exp(-0.5*std::pow((x-_mu)/_sigma,2));
    return _amp*e/_sigma/std::sqrt(2.*PI);
}

//----------------------------------------------------------------------------
std::ostream &gauss::to_stream(std::ostream &stream) const
{
    return stream;
}
