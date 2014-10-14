//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "output_config.hpp"

//----------------------------------------------------------------------------
output_config::output_config(bool l,bool a,size_t t):
    _long(l),
    _with_attributes(a),
    _trim_level(t)
{}

//----------------------------------------------------------------------------
bool output_config::long_output() const
{
    return _long;
}

//----------------------------------------------------------------------------
bool output_config::with_attributes() const
{
    return _with_attributes;
}

//----------------------------------------------------------------------------
size_t output_config::trim_level() const
{
    return _trim_level;
}

//---------------------------------------------------------------------------
void output_config::trim_level(size_t l)
{
    _trim_level = l;
}
