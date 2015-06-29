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
// Created on: May 12,2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <limits>
#include <ios>
#include <iomanip>
#include "operation.hpp"

operation::operation():
    _oconfig()
{}

//-----------------------------------------------------------------------------
operation::~operation()
{}

//-----------------------------------------------------------------------------
const output_config &operation::output_configuration() const
{
    return _oconfig;
}

//-----------------------------------------------------------------------------
void operation::output_configuration(const output_config &c)
{
    _oconfig = c;
}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const operation &op)
{
    return op.stream_result(o);
}

