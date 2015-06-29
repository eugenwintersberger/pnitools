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
// Created on: Jun 29,2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "output_config.hpp"

using namespace pni::core;

output_config::output_config():
    _channel_output(true),
    _channel_separator("\n")
{}

//----------------------------------------------------------------------------
output_config::output_config(bool channel_output,string channel_separator):
    _channel_output(channel_output),
    _channel_separator(channel_separator)
{}

//----------------------------------------------------------------------------
output_config::output_config(const output_config &c):
    _channel_output(c._channel_output),
    _channel_separator(c._channel_separator)
{}

//----------------------------------------------------------------------------
bool output_config::channel_output() const
{
    return _channel_output;
}

//----------------------------------------------------------------------------
string output_config::channel_separator() const
{
    return _channel_separator;
}
