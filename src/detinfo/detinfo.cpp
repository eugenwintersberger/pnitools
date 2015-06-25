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
// Created on: 23.08.2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include<iostream>
#include<vector>

#include "../common/exceptions.hpp"

#include "types.hpp"
#include "config.hpp"
#include "utils.hpp"
#include "detector_info.hpp"


int main(int argc,char **argv)
{

    //get programm configuration - abort if this fails
    configuration config = parse_configuration(argc,argv);

    //get output format - abort if this fails

    formatter_ptr formatter;
    if(!get_output_formatter(config,formatter)) return 1;

    //select the output stream
    std::ostream &output_stream = std::cout;

    //get input files - abort if there is a problem here
    file_list input_files;
    if(!get_input_files(config,input_files)) return 1;

    //-----------------------here comes the real business----------------------
    try
    {
        formatter->header(output_stream);
        //-------------------processing input files--------------------------------
        for(auto file: input_files)
        {
            detector_info_list infos = get_info(file);
            if(infos.empty()) continue;

            for(auto info: infos) 
            {
                formatter->detector_header(output_stream);
                formatter->write(output_stream,info);
                formatter->detector_footer(output_stream);
            }

        }
        formatter->footer(output_stream);
    }
    catch(file_error &error)
    {
        std::cerr<<error.description()<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"An unknown exception occured during file processing!";
        std::cerr<<std::endl;
        return 1;
    }
    return 0;
}


