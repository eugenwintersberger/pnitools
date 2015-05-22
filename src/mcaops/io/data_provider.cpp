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
// Created on: May 21, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "data_provider.hpp"

data_provider::data_provider():
    _index_gen()
{}

//----------------------------------------------------------------------------
data_provider::data_provider(const index_generator &g):
    _index_gen(g)
{}

//----------------------------------------------------------------------------
data_provider :: ~data_provider()
{ }

//----------------------------------------------------------------------------
index_generator data_provider::create_generator() const
{
    return _index_gen;
}
