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
#include <pni/io/exceptions.hpp>
#include "operations/operation.hpp"
#include "operations/operation_factory.hpp"
#include "command_predicate.hpp"
#include "utils.hpp"


using namespace pni::core;

//=============================================================================
// define some useful types
//=============================================================================
typedef std::vector<string>         args_vector;
typedef operation::pointer_type     operation_ptr;
typedef operation::data_range       data_range;


//=============================================================================
int main(int argc,char **argv)
{
    //check the total number of arguments and options and show a message if
    //they are not correct.

    if(!check_argument_count(argc)) return 1;

    //-------------------------------------------------------------------------
    // parse program options, create and configure the operation
    //-------------------------------------------------------------------------
    args_vector args = cliargs2vector(argc,argv);
    auto args_begin  = args.begin();
    auto args_end    = args.end();
    auto cmd_iter    = std::find_if(args_begin,args_end,command_predicate());

    args_vector   global_args(args_begin,cmd_iter);
    operation_ptr ops;  
    if(cmd_iter != args_end)
    {
        //create operation and configure it
        ops = operation_factory::create(*cmd_iter);
        args_vector res = ops->configure(args_vector(cmd_iter+1,args_end));

        //append the residual aruments to the global opptions
        std::copy(res.begin(),res.end(),std::back_inserter(global_args));
    }
    //now we can assemble the new options and argument vector from the 
    configuration config = create_global_config();

    try
    {
        parse(config,global_args,true);
    }
    catch(range_error &error)
    {
        std::cerr<<error.description()<<std::endl<<std::endl;
        std::cerr<<"Check your ROI or the numeric ranges for file patterns!";
        std::cerr<<std::endl;
        return 1;
    }

    if(manage_help_request(config)) return 1;
    
    //-------------------------------------------------------------------------
    // output the header if requested by the user
    //-------------------------------------------------------------------------
    if(config.value<bool>("header")) std::cout<<"#chan data"<<std::endl;
    
    //-------------------------------------------------------------------------
    // get the region of interrest if the user has set one
    //-------------------------------------------------------------------------
    roi_type roi;
    if(!get_roi(config,roi)) return 1;

    //------------------------------------------------------------------------
    // main processing loop -- loop over all input files
    //------------------------------------------------------------------------
    file_queue fileq;
    if(!get_file_queue(config,fileq)) return 1;

    while(!fileq.empty())
    {
        //---------------------------------------------------------------------
        // constructing the provider for input data
        //---------------------------------------------------------------------
        provider_ptr provider;
        if(!get_provider(fileq.front().path(),config,provider)) return 1;

        //--------------------------------------------------------------------
        // perform the operation on the data
        //--------------------------------------------------------------------
        while(!provider->finished())
        {
            try
            {
                //get the next data set 
                auto data = provider->next();

                data_range channel_range(data.first.begin(),data.first.end());
                data_range mca_range(data.second.begin(),data.second.end());

                if(config.has_option("roi"))
                    apply_roi_to_iterators(roi,channel_range.first,
                                               channel_range.second,
                                               mca_range.first,
                                               mca_range.second);

                operation::argument_type arg(channel_range,mca_range);

                (*ops)(arg);
                std::cout<<*ops<<std::endl;
            }
            catch(value_error &error)
            {
                std::cerr<<error.description()<<std::endl; return 1;
            }
            catch(size_mismatch_error &error)
            {
                std::cerr<<error.description()<<std::endl; return 1;
            }
            catch(shape_mismatch_error &error)
            {
                std::cerr<<error.description()<<std::endl; return 1;
            }
            catch(pni::io::io_error &error)
            {
                std::cerr<<error.description()<<std::endl; return 1;
            }
        }

        fileq.pop();
    }
    
    return 0;
}

