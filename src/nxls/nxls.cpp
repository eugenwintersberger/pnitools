//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: 30.06.2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include "nxls.hpp"
#include "../common/config_utils.hpp"
#include "nexus_tree_aggregation.hpp"

static const string program_name = "nxls";
static const string help_header = "nxls takes the following command line options";

int main(int argc,char **argv)
{
    //create configuration
    configuration config;
    config.add_option(config_option<bool>("help","h",
                "show help text",false));
    config.add_option(config_option<bool>("recursive","r",
                "traverse the Nexus tree recursively",false));
    config.add_option(config_option<bool>("show-attributes","a",
                "show attributes",false));
    config.add_argument(config_argument<string>("nxpath",-1));

    if(argc<2)
    {
        std::cerr<<"insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use nxls -h for help"<<std::endl;
        return 1;
    }

  
    //parse command line options and arguments
    if(parse_cli_opts(argc,argv,program_name,config)) return 1;

    //check if the user requested help 
    if(check_help_request(config,help_header)) return 1;


    try
    {
        nxpath path = nxpath::from_string(config.value<string>("nxpath"));
        h5::nxfile file = h5::nxfile::open_file(path.filename(),true);
        h5::nxobject root = file.root();

        //get the root object from where to start
        root = get_object(root,path);
        
        std::vector<string> path_v;
        aggregate_nexus_path(root,path_v,
                  config.value<bool>("recursive"),
                  config.value<bool>("show-attributes"));

#ifdef NOFOREACH
        BOOST_FOREACH(auto p,path_v)
#else
        for(auto p: path_v)
#endif
            std::cout<<p<<std::endl;

    }
   catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::core::index_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::io::object_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }


	return 0;
}

