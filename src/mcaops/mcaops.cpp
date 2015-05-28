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
#include <pni/core/arrays/slice.hpp>
#include <pni/io/parsers.hpp>
#include "operations/operation.hpp"
#include "operations/operation_factory.hpp"
#include "io/data_provider.hpp"
#include "io/data_provider_factory.hpp"
#include "command_predicate.hpp"


using namespace pni::core;
using namespace pni::io;


std::istream &operator>>(std::istream &stream,slice &s)
{
    typedef parser<string::const_iterator,slice> parser_type;

    parser_type p;
    string data;
    stream>>data;
    s = p(data);

    return stream;
}


//-----------------------------------------------------------------------------
void apply_roi(operation::data_range &range,const slice &roi)
{
    range.second = range.first;
    std::advance(range.first,roi.first());
    std::advance(range.second,roi.last());
}

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

    config.add_option(config_option<slice>("roi","r",
                "ROI for the input data"));

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
    
    typedef std::vector<string> args_vector;
    typedef operation::pointer_type operation_ptr;
    typedef data_provider::pointer_type provider_ptr;

    configuration config = create_global_config();

    //-------------------parse and store program options-----------------------
    args_vector args = cliargs2vector(argc,argv);
    auto args_begin = args.begin();
    auto args_end   = args.end();
    auto cmd_iter = std::find_if(args_begin,args_end,command_predicate());
    string cmd_name = *cmd_iter; //get the command name
    //generate a dummy operation
    operation_ptr ops = operation_factory::create(cmd_name);

    args_vector res = ops->configure(args_vector(cmd_iter+1,args_end));

    //now we can assemble the new options and argument vector from the 
    args_vector global_args = args_vector(args_begin,cmd_iter);

    parse(config,global_args,true);

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
    // constructing the provider for input data
    //-------------------------------------------------------------------------
    provider_ptr provider = data_provider_factory::create(config);
    
    //-------------------------------------------------------------------------
    //perform the operation
    //-------------------------------------------------------------------------
    if(config.value<bool>("header"))
        std::cout<<"#chan data"<<std::endl;


    while(!provider->finished())
    {
        try
        {
            //get the next data set 
            auto data = provider->next();

            typedef operation::data_range data_range;
            data_range channel_range(data.first.begin(),data.first.end());
            data_range mca_range(data.second.begin(),data.second.end());

            if(config.has_option("roi"))
            {
                auto roi = config.value<slice>("roi");
                apply_roi(channel_range,roi);
                apply_roi(mca_range,roi);
            }

            operation::argument_type arg(channel_range,mca_range);

            (*ops)(arg);
            std::cout<<*ops<<std::endl;
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

