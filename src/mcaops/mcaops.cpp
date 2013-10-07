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
 * Created on: 03.06.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include "mcaops.hpp"


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

   
    //-------------------------------------------------------------------------
    //options for the rebin command
    configuration rebin_config = create_rebin_config();

    //-------------------------------------------------------------------------
    //options for the scale command
    configuration scale_config = create_scale_config();

    //-------------------parse and store program options-----------------------
    std::vector<string> args = cliargs2vector(argc,argv);
    std::vector<string> cmd_args;
    cmd_args = parse(config,args,true);

    if(config.value<bool>("help"))
    {
        std::cerr<<usage_string<<std::endl<<std::endl;
        std::cerr<<command_string<<std::endl;
        std::cerr<<config<<std::endl;
        std::cerr<<std::endl<<"Options for the scale command:"<<std::endl;
        std::cerr<<scale_config<<std::endl;
        std::cerr<<std::endl<<"Options for the rebin command:"<<std::endl;
        std::cerr<<rebin_config<<std::endl;
        std::cerr<<"See 'man mcaops' for more information!"<<std::endl;
        return -1;
    }


    //-------------------------------------------------------------------------
    //here we will read data either from the standard in or from a file 
    operation::array_type data,channels;

    if(config.has_option("input"))
    {
        //read channel and mca data from a file
        read_from_file(config.value<string>("input"),channels,data,
                       config.value<string>("xcolumn"),
                       config.value<string>("ycolumn"));
    }
    else
    {
        //read channel and mca data from stdandard input
        read_from_stdin(channels,data);
    }


    //need to choose an operation
    if(!config.has_option("command"))
    {
        std::cerr<<"No command specified!"<<std::endl<<std::endl;
        std::cerr<<usage_string<<std::endl;
        return 1;
    }


    op_ptr optr;

    if(config.value<string>("command") == "scale")
    {
        parse(scale_config,cmd_args,true);
        optr = select_operator(config,scale_config);
    }
    else if(config.value<string>("command") == "rebin")
    {
        parse(rebin_config,cmd_args,true);
        optr = select_operator(config,rebin_config);
    }
    else
        optr = select_operator(config,config);

    //run the operation
    (*optr)(channels,data);

    if(config.value<bool>("header"))
        std::cout<<"#chan data"<<std::endl;

    //output result data
    std::cout<<*optr<<std::endl;

    
    return 0;
}

