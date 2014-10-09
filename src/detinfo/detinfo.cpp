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

#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/tiff/tiff_reader.hpp>

#include <pni/core/configuration.hpp>
#include "../common/file_list_parser.hpp"
#include "../common/exceptions.hpp"
#include "../common/config_utils.hpp"
#include "../common/file_utils.hpp"

#include "types.hpp"
#include "config.hpp"
#include "utils.hpp"
#include "detector_info.hpp"
#include "formatter_factory.hpp"

typedef std::unique_ptr<output_formatter> formatter_ptr;

const static string help_header = "detinfo takes the following command line options";
const static string prog_name = "detinfo";

int main(int argc,char **argv)
{

    if(argc <= 1)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use detinfo -h for help  ..."<<std::endl;
        return 1;
    }

    configuration config = create_configuration();
    try
    {
        //------------------managing command line parsing----------------------
        if(parse_cli_opts(argc,argv,prog_name,config)) return 1;

        //check for help request by the user
        if(check_help_request(config,help_header)) return 1;
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    auto format = config.value<string>("format");
    formatter_ptr formatter(formatter_factory::output(format));

    //-----------------------here comes the real business----------------------
    try
    {
        //retrieve list of input files passed by the user
        auto name_list = config.value<string_list>("input-files");
        auto infiles = file_list_parser::parse<file_list>(name_list);

        formatter->header(std::cout);
        //-------------------processing input files--------------------------------
        for(auto file: infiles)
        {
            detector_info_list infos = get_info(file);
            if(infos.empty()) continue;

            formatter->file_header(std::cout);
            for(auto info: infos) 
            { 
                formatter->write(std::cout,info);
                std::cout<<std::endl;
            }
            formatter->file_footer(std::cout);

        }
        formatter->footer(std::cout);
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    return 0;
}


