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

#include "config.hpp"
#include "../common/config_utils.hpp"
#include <pni/core/types.hpp>
#include <cstdlib>

static const string program_name = "nxls";
static const string help_header = "nxls takes the following command line options";

//----------------------------------------------------------------------------
configuration create_config()
{
    configuration config;
    config.add_option(config_option<bool>("help","h",
                "show help text",false));
    config.add_option(config_option<bool>("recursive","r",
                "traverse the Nexus tree recursively",false));
    config.add_option(config_option<bool>("show-attributes","a",
                "show attributes",false));
    config.add_argument(config_argument<string>("nxpath",-1));

    return config;
}

//----------------------------------------------------------------------------
configuration get_config(int argc,char **argv)
{

    configuration config = create_config();

    if(argc<2)
    {
        std::cerr<<"insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use nxls -h for help"<<std::endl;
        std::exit(1);
    }

  
    //parse command line options and arguments
    if(parse_cli_opts(argc,argv,program_name,config)) std::exit(1);

    //check if the user requested help 
    if(check_help_request(config,help_header)) std::exit(1);

    return config;

}
