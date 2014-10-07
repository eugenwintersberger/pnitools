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

typedef std::unique_ptr<pni::io::image_reader> reader_ptr;

const static string help_header = "detinfo takes the following command line options";
const static string prog_name = "detinfo";


int main(int argc,char **argv)
{
    configuration config = create_configuration();

    if(argc <= 1)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use detinfo -h for help  ..."<<std::endl;
        return 1;
    }

    //------------------managing command line parsing--------------------------
    if(parse_cli_opts(argc,argv,prog_name,config)) return 1;

    //check for help request by the user
    if(check_help_request(config,help_header)) return 1;


    //-----------------------here comes the real business----------------------
    try
    {
        //-------------------obtain input files------------------------------------
        if(config.value<bool>("verbose")) 
            std::cout<<"Checking input files ..."<<std::endl;

        auto name_list = config.value<string_list>("input_files");
        auto infiles = file_list_parser::parse<file_list>(name_list);

        //-------------------processing input files--------------------------------
        reader_ptr reader;
        pni::io::image_info info;

        bool print_nx = config.value<bool>("nx");
        bool print_ny = config.value<bool>("ny");
        bool print_ntot = config.value<bool>("ntot");
        bool print_type = config.value<bool>("dtype");

        for(auto file: infiles)
        {
            detector_info_list info = get_info(file);
          
            /*
            if(print_nx) std::cout<<info.nx()<<std::endl;
            else if(print_ny) std::cout<<info.ny()<<std::endl;
            else if(print_ntot) std::cout<<info.npixels()<<std::endl;
            else if(print_type)
                std::cout<<info.get_channel(0).type_id()<<std::endl;
            else if(config.value<bool>("list-files"))
                std::cout<<file.path()<<std::endl;
            else
            {

                if(config.value<bool>("full-path"))
                    std::cout<<file.path();
                else
                    std::cout<<file.name();
                std::cout<<" ("<<info.nx()<<" x "<<info.ny()<<") ntot = "<<info.npixels();
                std::cout<<" type = "<<info.get_channel(0).type_id()<<std::endl;
            }
            */

        }
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    return 0;
}


