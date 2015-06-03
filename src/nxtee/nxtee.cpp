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
//************************************************************************
// Created on: Jul 18,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <iostream>
#include <fstream>

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

#include "utils.hpp"

using namespace pni::io::nx;
using namespace pni::core;

static const string program_name = "nxtee";
static const string help_header = 
"Program usage:\n  nxtee NEXUSPATH";





int main(int argc,char **argv)
{
    //-------------------------------------------------------------------------
    //before anything else we check if the user has provided enough command line
    //arguments
    if(argc<2)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use nxtee -h for help  ..."<<std::endl;
        return 1;
    }

    configuration config = create_global_config();
    parse(config,cliargs2vector(argc,argv));

    //------------------------------------------------------------------------
    // check command line options
    //------------------------------------------------------------------------
    if(show_help(config)) return 1;
    if(no_target_path(config)) return 1;
    
    //------------------------------------------------------------------------
    // retrieve the target object
    //------------------------------------------------------------------------

    //retrieve the path to the target
    auto target_path = config.value<nxpath>("target");

    //get the file
    h5::nxfile file; 
    if(!get_target_file(target_path,file)) return 1;
    
    //get the object in the file
    h5::nxobject target;
    if(!get_target_object(target_path,file,target)) return 1;

    
    //------------------------------------------------------------------------
    // perform operation
    //------------------------------------------------------------------------





    //in case of success we return 0
    return 0;
}
