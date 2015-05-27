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
// Created on: May 27,2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "dump_operation.hpp"

//----------------------------------------------------------------------------
dump_operation::dump_operation():operation()
{}

//---------------------------------------------------------------------
//! destructor
dump_operation::~dump_operation()
{}

//---------------------------------------------------------------------
//! execute operation
void dump_operation::operator()(const argument_type &data)
{
    _data = data;
}

//---------------------------------------------------------------------
//! write result to output stream
std::ostream &dump_operation::stream_result(std::ostream &o) const
{
    auto citer = _data.first.begin();
    auto diter = _data.second.begin();

    while(citer!=_data.first.end())
        o<<*citer++<<"\t"<<*diter++<<std::endl;

    return o;
}
