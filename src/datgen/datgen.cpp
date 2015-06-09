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
#include "grid_generator_builder.hpp"
#include "grid_generator.hpp"
#include "functors/functor.hpp"
#include "functors/functor_factory.hpp"
#include "functors/executor.hpp"

using namespace pni::core;


int main(int argc,char **argv)
{
    configuration global_config = create_global_config();

    //------------------------------------------------------------------------
    // split configuration for the different generators
    //------------------------------------------------------------------------
    options_splitter splitter(args_vector{"uniform","gauss","linear"});
    args_map m=splitter(cliargs2vector(argc,argv));

    if(m.empty())
    {
        std::cerr<<"No command line arguments passed!"<<std::endl
                 <<"use datgen -h for help!"<<std::endl;
        return 1;
    }

    //parse the global configuration
    parse(global_config,m.find("global")->second);
    //remove the global options from the map
    m.erase(m.find("global")); 

    //------------------------------------------------------------------------
    // build the grid generator
    //------------------------------------------------------------------------
    grid_generator g;
    try
    {
        g = grid_generator_builder::build(global_config);
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(range_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    //------------------------------------------------------------------------
    // assemble the functor stack here
    //------------------------------------------------------------------------
    functor_vector funcs;

    for(auto f: m)
        funcs.push_back(functor_factory::create(f.first,f.second));

    executor exe(std::move(funcs));

    //------------------------------------------------------------------------
    // these are the main loops of the program
    //------------------------------------------------------------------------
    for(size_t grid_index=0;
        grid_index<global_config.value<size_t>("steps");
        grid_index++)
    {
        float64 x = g();

        if(global_config.value<bool>("show-grid"))
            std::cout<<x<<"\t";

        std::cout<<exe(x)<<std::endl;
    }


    

    return 0;
}
