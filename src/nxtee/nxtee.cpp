/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 18,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <iostream>
#include <fstream>

#include <pni/core/config/config_parser.hpp>
#include <pni/core/config/configuration.hpp>

#include "../common/config_utils.hpp"
#include "nxtee.hpp"

static const string program_name = "nxtee";
static const string help_header = 
"Program usage:\n  nxtee NEXUSPATH";


int main(int argc,char **argv)
{
    //-------------------------------------------------------------------------
    //before anything else we check if the user has provided enough command line
    //arguments
    if(argc<2)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use nxtee -h for help  ..."<<std::endl;
        return 1;
    }

    //-------------------------------------------------------------------------
    //start here with program configuration
    configuration config;

    config.add_option(config_option<bool>("help","h",
                "show help text",false));
    config.add_argument(config_argument<string>("nexus-path",-1));

    //-------------------------------------------------------------------------
    //parse the command line arguments
    try
    {
        if(parse_cli_opts(argc,argv,program_name,conf))
            return 1;
       
        if(check_help_request(conf,help_header)) 
            return 1;
    }
    catch(pni::core::cli_option_error &error)
    {
        std::cerr<<"Error during parsing command line options and arguments!";
        std::cerr<<std::endl;
        std::cerr<<error<<std::endl;
        return 1;
    }

    //=========================================================================
    //start here with program main loop
    try
    {
        //first we need to obtain the target object - we assume that it already
        //exists
        nxpath path = path_from_string(config.value<string>("nexus-path"));
        //open the file in read-write mode
        h5::nxfile file = h5::open_file(path.filename(),false);
        nxobject_t root = h5::nxgroup(file["/"]);

        nxobject_t target = get_object(root,path);


    }
    catch(....)
    {
        std::cerr<<"Unkown error - something went wrong!"<<std::endl;
        return 1;
    }

    //in case of success we return 0
    return 0;
}
