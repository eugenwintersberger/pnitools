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
// Created on: 03.06.2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include "operation.hpp"
#include "io/data_provider.hpp"
#include "io/data_provider_factory.hpp"

using namespace pni::core;

//-----------------------------------------------------------------------------
configuration create_global_config()
{
    configuration config;

    //----------------setting up the program options---------------------------
    //these options do not show up in the help text
    config.add_argument(config_argument<string>("command",1));
    config.add_argument(config_argument<string>("input",2));

    //-------------------------------------------------------------------------
    //global options valid for all commands
    config.add_option(config_option<bool>("help","h","show help text",false));
    config.add_option(config_option<bool>("verbose","v","show verbose output",
                                          false));
    config.add_option(config_option<bool>(
                "header","","write headers before output",false));

    config.add_option(config_option<string>("channels","c",
                "name of the column with bin center values"));
    config.add_option(config_option<string>("bins","b",
                "name of the column with the center values"));
    config.add_option(config_option<string>("mca","m",
                "name of the MCA columns"));
    config.add_option(config_option<size_t>("auto-index-offset","",
                "offset for automatic channel index",size_t(0)));
    
    config.add_option(config_option<size_t>("mca-size","s",
                "number of channels of a single MCA spectrum",size_t(0)));

    return config;
}


//=============================================================================
static const char usage_string[] = 
                      "Program usage:\n\n mcaops <command> <global options>"
                      " <command specific options> [input file]";

static const char command_string[] = 
            "Commands supported by mcaops:\n"
            "  sum\tum over all channels in a spectrum\n"
            "  max\tosition of maximum and its value\n"
            "  rebin\tre-bin the spectrum\n"
            "  scale\tscale the channel numbers to units\n"
            ;

//=============================================================================
int main(int argc,char **argv)
{
    //check the total number of arguments and options and show a message if
    //they are not correct.
    if(argc<2)
    {
        std::cout<<usage_string<<std::endl;
        std::cout<<"\nuse mcatool -h for more information"<<std::endl;
        return 1;
    }
    configuration config = create_global_config();

    //-------------------parse and store program options-----------------------
    std::vector<string> args = cliargs2vector(argc,argv);
    std::vector<string> cmd_args; 
    cmd_args = parse(config,args,true);

    //cmd_args are those arguments not consumed by the global parser but 
    //are rather used for the configuration of the different commands

    if(config.value<bool>("help"))
    {
        std::cerr<<usage_string<<std::endl<<std::endl;
        std::cerr<<command_string<<std::endl;
        std::cerr<<config<<std::endl;
        return 1;
    }


    //-------------------------------------------------------------------------
    //Get the command
    //-------------------------------------------------------------------------
    //need to choose an operation
    if(!config.has_option("command"))
    {
        std::cerr<<"No command specified!"<<std::endl<<std::endl;
        std::cerr<<usage_string<<std::endl;
        return 1;
    }

    //-------------------------------------------------------------------------
    // constructing the provider for input data
    //-------------------------------------------------------------------------
    data_provider::pointer_type provider =
        data_provider_factory::create(config);
    
    //-------------------------------------------------------------------------
    //perform the operation
    //-------------------------------------------------------------------------
    if(config.value<bool>("header"))
        std::cout<<"#chan data"<<std::endl;

    while(!provider->finished())
    {
        try
        {
            std::cout<<provider->next()<<std::endl;
            //(*ops_ptr)(provider_ptr->next());  //run the operation
        }
        catch(value_error &error)
        {
            std::cerr<<error<<std::endl; return 1;
        }
        catch(size_mismatch_error &error)
        {
            std::cerr<<error<<std::endl; return 1;
        }
        catch(shape_mismatch_error &error)
        {
            std::cerr<<error<<std::endl; return 1;
        }
    }
    
    return 0;
}

