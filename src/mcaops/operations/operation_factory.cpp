//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 10,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <limits>
#include <ios>
#include <iomanip>
#include "operation_factory.hpp"

#include "sum_operation.hpp"
#include "dump_operation.hpp"
#include "max_operation.hpp"



using namespace pni::core;

operation::pointer_type operation_factory::create(const configuration &config)
{
    typedef operation::pointer_type pointer_type;

    //check if command argument has been provided by the user - throw an 
    //exception if not
    if(!config.has_option("command"))
        throw cli_error(EXCEPTION_RECORD,"No command passed - aborting!");

    auto command = config.value<string>("command");
    if(command == "sum")
        return pointer_type(new sum_operation());
    else if(command == "dump")
        return pointer_type(new dump_operation());
    else if(command == "max")
        return pointer_type(new max_operation());
    else
        throw key_error(EXCEPTION_RECORD,"Unknown operation ["+command+"]!");
}


