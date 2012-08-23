/*
 * main.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: Eugen Wintersberger
 */

#include<iostream>

#include "../common/Exceptions.hpp"
#include "../common/ProgramConfig.hpp"


int main(int argc,char **argv)
{
    ProgramConfig config;

    //---------------------setup program configuration-------------------------
    config.add_option(ConfigOption<String>("test","t","a stupid option"),true);

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
        std::cerr<<"For useage information use: "<<std::endl;
        std::cerr<<"    detinfo -h"<<std::endl;

        return 1;
    }

    //-------------------obtain input files------------------------------------


    return 0;
}


