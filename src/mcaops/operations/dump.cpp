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

#include "dump.hpp"

//----------------------------------------------------------------------------
dump::dump():operation()
{}

//----------------------------------------------------------------------------
//! destructor
dump::~dump()
{}

//----------------------------------------------------------------------------
operation::args_vector dump::configure(const args_vector &args)
{ 
    return args;
}

//----------------------------------------------------------------------------
//! execute operation
void dump::operator()(const argument_type &data)
{
    _data = data;
}

//----------------------------------------------------------------------------
//! write result to output stream
std::ostream &dump::stream_result(std::ostream &o) const
{
    auto &channel_range = _data.first;
    auto &mca_range     = _data.second;
    auto citer = channel_range.first;
    auto diter = mca_range.first;

    const output_config &c = this->output_configuration();

    while(citer!=channel_range.second)
    {
        if(c.channel_output()) o<<*citer++<<"\t";
        else citer++;
        
        o<<*diter++<<c.channel_separator();
    }

    return o;
}
