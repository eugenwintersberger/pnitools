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
#include "grid_generator_builder.hpp"
#include "functors/functor_factory.hpp"

using namespace pni::core;

namespace std{
    istream &operator>>(istream &stream,type_id_t &tid)
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
    c.add_option(config_option<type_id_t>("type","t",
                "Type code of the requested data type",
                type_id_t::FLOAT64));
    c.add_option(config_option<bool>("show-grid","",
                "Show x grid values",false));

    return c;
}

//----------------------------------------------------------------------------
bool show_help(const configuration &global_config)
{
    if(global_config.value<bool>("help"))
    {
        std::cerr<<"Global program options:"<<std::endl<<std::endl;
        std::cerr<<global_config<<std::endl<<std::endl;
        std::cerr<<"Options for uniform random numbers:"
                 <<std::endl<<std::endl;
        std::cerr<<functor_factory::config("uniform")
                 <<std::endl<<std::endl;
        std::cerr<<"Options for linear function:"<<std::endl<<std::endl;
        std::cerr<<functor_factory::config("linear")
                 <<std::endl<<std::endl;
        std::cerr<<"Options for gauss function:"<<std::endl<<std::endl;
        std::cerr<<functor_factory::config("gauss")
                 <<std::endl;
        return true;
    }

    return false;
}

//------------------------------------------------------------------------
bool build_grid_generator(const configuration &global_config,
                          grid_generator &generator)
{
    try
    {
        generator = grid_generator_builder::build(global_config);
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }
    catch(range_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }

    return true;
}

//----------------------------------------------------------------------------
bool build_executor(const args_map &args,executor &exe)
{

    functor_vector funcs;

    for(auto arg: args)
    {
        try
        {
            funcs.push_back(functor_factory::create(arg.first,arg.second));
        }
        catch(cli_option_error &error)
        {
            std::cerr<<error.description()<<std::endl;
            return false;
        }
        catch(range_error &error)
        {
            std::cerr<<error.description()<<std::endl;
            return false;
        }
    }

    exe = executor(std::move(funcs));
    return true;
}

//----------------------------------------------------------------------------
bool check_arguments(const args_map &args)
{
    if(args.empty())
    {
        std::cerr<<"No command line arguments passed!"<<std::endl
                 <<"use datgen -h for help!"<<std::endl;
        return false;
    }
    else if(args.size()==1)
    {
        std::cerr<<"No or unknown functor name provided - aborting!"<<std::endl;
        std::cerr<<"For more help use: datgen -h"<<std::endl;
        return false;
    }

    return true;
}

//----------------------------------------------------------------------------
bool parse_global_config(configuration &global_config, args_map &args)
{
    //parse the global configuration
    try
    {
        parse(global_config,args.find("global")->second);
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return false;
    }
    catch(type_error &error)
    {
        std::cerr<<error.description()<<std::endl<<std::endl;
        std::cerr<<"Check the value of the -t option!"<<std::endl;
        std::cerr<<"This option can be either 'int' or 'float'!"<<std::endl;
        return false;
    }
    
    //remove the global options from the map
    args.erase(args.find("global")); 
    return true;
}
