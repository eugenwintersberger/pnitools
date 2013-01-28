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
 * Created on: Oct 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include<iostream>

#include <pni/core/types.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/io/nx/nx.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "xml_utils.hpp"
#include "../common/nx_object_path.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;
namespace tree = boost::property_tree;



int main(int argc,char **argv)
{
    configuration conf;
    conf.add_option(config_option<nx_object_path>("parent","p",
                "path to the parent object"));
    conf.add_option(config_option<bool>("append","a",
                "append structure to existing file"));
    conf.add_argument(config_argument<string>("input_file",-1));
   
    //show usage message
    if(argc <= 1)
    {
        std::cerr<<"Program usage: "<<std::endl<<std::endl;
        std::cerr<<"xml2nx [OPTIONS] INPUTFILE"<<std::endl<<std::endl;
        std::cerr<<"for more details use: xml2nx -h"<<std::endl;
        return 1;
    }

    //parse command line options and arguments
    try
    {
        parse(conf,argc,(const char**)argv);
    }
    catch(cli_help_request &error)
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }
    
    //read the XML data 
    tree::ptree xmltree; 
    try
    {
        tree::read_xml(conf.value<string>("input_file"),xmltree);
    }
    catch(...)
    {
        std::cerr<<"Error reading XML file ";
        std::cerr<<conf.value<string>("input_file")<<"!"<<std::endl;
        return 1;
    }


    //get the target file
    auto opath = conf.value<nx_object_path>("parent");
    nxfile file;
    if(conf.value<Bool>("append"))
    {
        try
        {
            file = nxfile::open_file(opath.filename(),false);
        }
        catch(pni::io::nx::nxfile_error &error)
        {
            std::cerr<<"Error opening file "<<opath.filename();
            std::cerr<<"for writing data"<<std::endl<<std::endl;
            std::cerr<<error<<std::endl;
            return 1;
        }
    }
    else
    {
        try
        {
            file = nxfile::create_file(opath.filename(),false,0);
        }
        catch(pni::io::nx::nxfile_error &error)
        {
            std::cerr<<"Error creating file "<<opath.filename();
            std::cerr<<"for writing data!"<<std::endl<<std::endl;
            std::cerr<<error<<std::endl;
            return 1;
        }
    }

    //get the group where to append XML data
    nxgroup target_group = file["/"];
    if(opath.object_path()!="")
    {
        try
        {
            target_group = file[opath.object_path()];
        }
        catch(pni::io::nx::nxgroup_error &error)
        {
            std::cerr<<"Error opening target group ";
            std::cerr<<opath.object_path()<<" to append object!";
            std::cerr<<std::endl<<std::endl;
            return 1;
        }
    }
   
    //create the objects below the target group
    create_objects(target_group,xmltree);


    file.close();
    return 0;
}
