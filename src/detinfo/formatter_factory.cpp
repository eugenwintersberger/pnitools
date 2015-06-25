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
// Created on: Oct 9,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "formatter_factory.hpp"
#include "simple_output_formatter.hpp"
#include "key_value_output_formatter.hpp"
#include "xml_output_formatter.hpp"
#include "csv_output_formatter.hpp"

output_formatter *formatter_factory::output(const string &name)
{
    if(name == "simple")
        return new simple_output_formatter();
    else if(name == "csv")
        return new csv_output_formatter();
    else if(name == "keyvalue")
        return new key_value_output_formatter();
    else if(name == "xml")
        return new xml_output_formatter();
    else
        throw value_error(EXCEPTION_RECORD,
                "Unknown output formatter ["+name+"]!");
}
