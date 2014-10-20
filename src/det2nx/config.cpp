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
// Created on: Oct 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <cstdlib>
#include "config.hpp"
#include "types.hpp"
#include "../common/config_utils.hpp"

static const string program_name = "det2nx";
static const string help_header = "det2nx takes the following command line options";

//------------------------------------------------------------------------
configuration create_default_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h",
                "show short help text",false));
    config.add_option(config_option<string>("group","g",
                "the detector group to store the data",
                "/:NXentry/:NXinstrument/:NXdetector"));
    config.add_option(config_option<string>("data","d",
                "the data field where to store data",
                "data"));

    //we do not add a default value here - the user has to pass 
    //this option
    config.add_option(config_option<string>("file","f",
                "the name of the nexus file"));

    config.add_option(config_option<bool>("verbose","v",
                "print verbose output",false));
    config.add_argument(config_argument<string_vector>("input-files",-1,
                string_vector()));
    config.add_option(config_option<bool>("overwrite","",
                "overwrite existing data file",false));
    config.add_option(config_option<size_t>("deflate","d",
                "set deflate level",size_t(0)));

    return config;
}

//----------------------------------------------------------------------------
int get_cli_config(int argc,char **argv,configuration &config)
{
    if(argc<2)
    {
        std::cerr<<"det2nx called with to less arguments!"<<std::endl;
        std::cerr<<std::endl<<"Use det2nx -h for more information"<<std::endl;
        return 1;
    }
  
    //parse command line options and arguments
    if(parse_cli_opts(argc,argv,program_name,config)) return 1;

    //check if the user requested help 
    if(check_help_request(config,help_header)) return 1;
}
