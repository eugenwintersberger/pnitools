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

#include <pni/utils/io/CBFReader.hpp>
#include <pni/utils/io/TIFFReader.hpp>

#include "../common/Exceptions.hpp"
#include "../common/ProgramConfig.hpp"
#include "../common/File.hpp"
#include "../common/FileList.hpp"

typedef std::vector<String> strlist;

int main(int argc,char **argv)
{
    ProgramConfig config;
    Bool verbose = false;

    //---------------------setup program configuration-------------------------
    config.add_option(ConfigOption<Bool>("verbose","v","be verbose",&verbose));
    config.add_option(ConfigOption<Bool>("full-path","",
                "show the full path on output"));
    config.add_argument(ConfigArgument<strlist>("input-files",-1));

    //------------------managing command line parsing--------------------------
    try
    {
        config.parse(argc,argv);
    }
    catch(CLIHelpRequest &error)
    {
        std::cerr<<config<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Error parsing command line - aborting!"<<std::endl;
        std::cerr<<"For useage information use: "<<std::endl<<std::endl;
        std::cerr<<"    detinfo -h"<<std::endl<<std::endl;

        return 1;
    }

    //-------------------obtain input files------------------------------------
    FileList infiles;
    
    if(verbose)
        std::cout<<"Checking input files ..."<<std::endl;
    try
    {
        auto path_list = config.value<strlist>("input-files");
        infiles = FileList(path_list);
    }
    catch(FileError &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

    //-------------------processing input files--------------------------------
    for(auto file: infiles)
    {
        pni::io::ImageInfo info;
        if(file.extension()==".cbf")
        {
            pni::io::CBFReader reader(file.path());
            info = reader.info(0);
        }
        else if(file.extension()==".tiff")
        {
            pni::io::TIFFReader reader(file.path());
            info = reader.info(0);

        }
        else
        {
            throw FileTypeError(EXCEPTION_RECORD,"File ["+file.path()+"] is of"
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


