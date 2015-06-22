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
#include <pni/io/formatters.hpp>
#include "datgen_utils.hpp"
#include "options_splitter.hpp"
#include "functors/functor.hpp"
#include "functors/functor_factory.hpp"
#include "functors/executor.hpp"

using namespace pni::core;
using namespace pni::io;


int main(int argc,char **argv)
{
    configuration global_config = create_global_config();

    //------------------------------------------------------------------------
    // split configuration for the different generators
    //------------------------------------------------------------------------
    options_splitter splitter(args_vector{"uniform","gauss","linear"});
    args_map m=splitter(cliargs2vector(argc,argv));
    
    if(!check_arguments(m)) return 1;

    //------------------------------------------------------------------------
    // parse the global configuration
    //------------------------------------------------------------------------
    parse_global_config(global_config,m);

    //show help text if requested by the user
    if(show_help(global_config)) return 1;

    //------------------------------------------------------------------------
    // build the grid generator
    //------------------------------------------------------------------------
    grid_generator g;
    if(!build_grid_generator(global_config,g)) return 1;

    //------------------------------------------------------------------------
    // assemble the functor stack here
    //------------------------------------------------------------------------
    executor exe;
    if(!build_executor(m,exe)) return 1;

    //------------------------------------------------------------------------
    // these are the main loops of the program
    //------------------------------------------------------------------------
    formatter<float64> float_formatter;
    formatter<int64>   int_formatter;

    for(size_t grid_index=0;
        grid_index < global_config.value<size_t>("steps");
        grid_index++)
    {
        float64 x = g();
        
        //compute the result
        float64 result = exe(x);

        if(global_config.value<bool>("show-grid"))
            std::cout<<float_formatter(x)<<"\t";
 
        switch(global_config.value<type_id_t>("type"))
        {
            case type_id_t::INT64:
                std::cout<<int_formatter(int64(result));break;
            case type_id_t::FLOAT64:
                std::cout<<float_formatter(result); break;
            default:
                throw type_error(EXCEPTION_RECORD,
                        "Unknown data type requested by user!");
        }
        std::cout<<std::endl;
    }

    return 0;
}
