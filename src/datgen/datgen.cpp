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
// Created on: 8 May, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include "datgen_utils.hpp"
#include "options_splitter.hpp"

using namespace pni::core;


int main(int argc,char **argv)
{
    configuration global_config = create_global_config();

    //------------------------------------------------------------------------
    // split configuration for the different generators
    //------------------------------------------------------------------------
    options_splitter splitter(args_vector{"uniform","gauss","linear"});
    args_map m=splitter(cliargs2vector(argc,argv));

    parse(global_config,m.find("global")->second);
    

    return 0;
}
