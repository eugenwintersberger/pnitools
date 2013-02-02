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
 * Created on: 23.08.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include<iostream>
#include<vector>

#include <pni/io/cbf_reader.hpp>
#include <pni/io/tiff_reader.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include "../common/file.hpp"
#include "../common/file_list.hpp"
#include "../common/exceptions.hpp"

typedef std::vector<string> strlist;

int main(int argc,char **argv)
{
    configuration config;
    bool verbose = false;

    if(argc <= 1)
    {
        std::cerr<<"Program usage: "<<std::endl<<std::endl;
        std::cerr<<"detinfo [OPTIONS] FILE [ FILE] .."<<std::endl<<std::endl;
        std::cerr<<"for more details use: detinfo -h"<<std::endl;
        return 1;
    }

    //---------------------setup program configuration-------------------------
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<bool>("verbose","v","be verbose",&verbose));
    config.add_option(config_option<bool>("full-path","",
                "show the full path on output",false));
    config.add_argument(config_argument<strlist>("input-files",-1,strlist{"-"}));

    //------------------managing command line parsing--------------------------
    try
    {
        parse(config,argc,(const char**)argv);
    }
    catch(...)
    {
        std::cerr<<"Wrong or insufficient command line options:"<<std::endl;
        std::cerr<<std::endl;
        std::cerr<<"use detinfo -h for more info"<<std::endl;
        return 1;
    }

    //check for help request by the user
    if(config.value<bool>("help"))
    {
        std::cerr<<"detinfo takes the following command line options";
        std::cerr<<std::endl<<std::endl;
        std::cerr<<config<<std::endl;
        return 1;
    }

    //-------------------obtain input files------------------------------------
    file_list infiles;
    
    if(verbose) std::cout<<"Checking input files ..."<<std::endl;

    try
    {
        auto path_list = config.value<strlist>("input-files");
        infiles = file_list(path_list);
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    //-------------------processing input files--------------------------------
    for(auto file: infiles)
    {
        pni::io::image_info info;
        if(file.extension()==".cbf")
        {
            pni::io::cbf_reader reader(file.path());
            info = reader.info(0);
        }
        else if(file.extension()==".tiff")
        {
            pni::io::tiff_reader reader(file.path());
            info = reader.info(0);
        }
        else
        {
            throw file_type_error(EXCEPTION_RECORD,"File ["+file.path()+"] is of"
                    "unknown type!");
        }

        if(config.value<bool>("full-path"))
            std::cout<<file.path();
        else
            std::cout<<file.name();

        std::cout<<" ("<<info.nx()<<" x "<<info.ny()<<") ntot = "<<info.npixels();
        std::cout<<" type = "<<info.get_channel(0).type_id()<<std::endl;

    }

    return 0;
}


