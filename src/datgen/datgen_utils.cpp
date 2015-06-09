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

#include "datgen_utils.hpp"

using namespace pni::core;

std::istream &operator>>(std::istream &stream,type_id_t &tid)
{
    string s;
    stream>>s;

    if(s=="int")
        tid=type_id_t::INT64;
    else if(s=="float")
        tid=type_id_t::FLOAT64;
    else
        throw type_error(EXCEPTION_RECORD,
                "Unkonwn type code ["+s+"]!");

    return stream;
}

//----------------------------------------------------------------------------
configuration create_global_config()
{
    configuration c; 

    c.add_option(config_option<bool>("help","h",
                "Show program help text",false));

    c.add_option(config_option<float64>("begin","b",
                "First grid value"));
    c.add_option(config_option<float64>("end","e",
                "Last grid value"));
    c.add_option(config_option<size_t>("steps","s",
                "Number of grid points"));
    c.add_option(config_option<size_t>("repeats","r",
                "Number of repititions",1));
    c.add_option(config_option<type_id_t>("type","t",
                "Type code of the requested data type"));
    c.add_option(config_option<string>("output","o",
                "Ouput file"));

    return c;
}
