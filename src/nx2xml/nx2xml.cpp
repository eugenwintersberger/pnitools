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
 * Created on: Jul 19, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <iostream>
#include "nx2xml.hpp"
#include "../common/config_utils.hpp"

static const string program_name = "nx2xml";
static const string help_header = "Program usage:\n  nx2xml [OPTIONS] INPUT FILE";

int main(int argc,char **argv)
{
    using xml::operator<<;
    configuration conf = create_config();

    if(argc<2)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use nx2xml -h for help  ..."<<std::endl;
        return 1;
    }

    //--------- setup CLI configuration ---------------------------------------
    try
    {
        if(parse_cli_opts(argc,argv,program_name,conf))
            return 1;
       
        if(check_help_request(conf,help_header)) 
            return 1;
    }
    catch(pni::core::cli_option_error &error)
    {
        std::cerr<<"Error during parsing command line options and arguments!";
        std::cerr<<std::endl;
        std::cerr<<error<<std::endl;
        return 1;
    }
  
    try
    {
        //we can savely open the Nexus file in read only mode
        h5::nxfile file = h5::nxfile::open_file(conf.value<string>("input-file"),true);
        nxobject_t root_group = h5::nxgroup(file["/"]);

        //create the XML tree
        xml::node root_node;
        xml::nexus2xml(root_group,root_node);
        
        //close the Nexus file
        file.close();

        //write XML file
        std::cout<<root_node<<std::endl;

    }
    catch(const pni::core::cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(nxfile_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(nxgroup_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    return 0;
}
