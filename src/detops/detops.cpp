/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Oct 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <iomanip>
#include "detops.hpp"
#include "io_utils.hpp"
#include "roi_utils.hpp"
#include "image_processor.hpp"
#include "integrate.hpp"
#include "minimum.hpp"
#include "maximum.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

void assemble_process_chain(const configuration &config,image_processor &proc)
{
    auto cmd = config.value<string>("command");

    if(cmd == "sum")
        proc.push_back(image_processor::op_ptr_type(new integrate()));
    else if(cmd == "max")
        proc.push_back(image_processor::op_ptr_type(new maximum()));
    else if(cmd == "min")
        proc.push_back(image_processor::op_ptr_type(new minimum()));
}

int main(int argc, char **argv) 
{

    configuration config = create_config();

    if(parse_cli_opts(argc,argv,"detops",config)) return 1;

    if(check_help_request(config,"")) return 1;

    //=========================basic input reading=============================
    //we try to do as much as possible before reading the list of input files.
    //As this list can be long and thus checking the files might take a while we
    //do not want to recognize right after this expensive job that we hat to
    //throw an exception due to some simple operation

    //select the command
    image_processor proc;
    
    //===============read darkfield and flatfield images========================
    try
    {
        //read dark- and flatfield image
        /*
        image_type dark_image = get_darkfield(config);
        image_type flat_image = get_flatfield(config);
        */

        //setup rois (if there are any)
        roi_stack rois = get_roi_stack(config);
   
        //generate the list of input files
        file_list input_files = get_input_files(config);

        //now we can start with the construction of the operation
        assemble_process_chain(config,proc);
     
#ifdef NOFOREACH
        BOOST_FOREACH(auto f,input_files)
#else
        for(auto f: input_files)
#endif
        {
           //read image from file
           image_type image = read_image(f); 
           //generate image stack from the image and rois
           image_stack istack;
           if(rois.empty())
               istack.push_back(image);
           else
               //here we most probably have to pass the dark and flat field
               //images - that would be the simplest approach
               istack= image_stack_from_rois(image,rois);

           //apply operation on each image
#ifdef NOFOREACH
           BOOST_FOREACH(auto i,istack)
#else
           for(auto i: istack) 
#endif
               proc(i);

           //show the result for the last operation
           std::cout<<std::setprecision(15)<<std::scientific;
           std::cout<<*proc.back()<<std::endl;
        }
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl; return 1;
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl; return 1;
    }
    catch(parser_error &error)
    {
        std::cerr<<error<<std::endl; return 1;
    }
    /*
    catch(...)
    {
        std::cerr<<"Something went wrong!"<<std::endl;
        return 1;
    }*/

	return 0;
}

