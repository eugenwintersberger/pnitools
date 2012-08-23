/*
 * main.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: Eugen Wintersberger
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


