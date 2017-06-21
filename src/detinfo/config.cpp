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
// Created on: Oct 7,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <cstdlib>
#include "types.hpp"
#include "config.hpp"
#include "../common/config_utils.hpp"

const static string help_header = "detinfo takes the following command line options";
const static string prog_name = "detinfo";


configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("format","f","output format",
                                            "simple"));
    config.add_argument(config_argument<string_list>("input-files",-1,
                        string_list({"-"})));

    return config;
}

//----------------------------------------------------------------------------
bool parse_configuration(int argc,char **argv,configuration &config)
{
    if(argc <= 1)
    {
        std::cerr<<"Insufficient number of command line arguments!";
        std::cerr<<std::endl;
        std::cerr<<"Use detinfo -h for help  ..."<<std::endl;
        return false;
    }

    try
    {
        //------------------managing command line parsing---------------------
        if(parse_cli_opts(argc,argv,prog_name,config)) return false;

        //check for help request by the user
        if(check_help_request(config,help_header)) return false;
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return false;
    }
    catch(...)
    {
        std::cerr<<"Unknown exception occured during command line parsing!";
        std::cerr<<std::endl<<"Program is aborting!"<<std::endl;
        return false;
    }

    return true;
}
