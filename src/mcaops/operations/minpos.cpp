//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: May 27, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "minpos.hpp"

//----------------------------------------------------------------------------
minpos::minpos(): operation(),_value(0)
{}

//----------------------------------------------------------------------------
minpos::~minpos(){}

//----------------------------------------------------------------------------
void minpos::operator()(const argument_type &data)
{
    auto iter = std::min_element(data.second.begin(),data.second.end());
    _value = data.first[std::distance(data.second.begin(),iter)];
}

//----------------------------------------------------------------------------
std::ostream &minpos::stream_result(std::ostream &o) const
{
    o<< _value;
    return o;
}
