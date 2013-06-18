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


#include "xml2nx.hpp"
#include "xml_utils.hpp"
#include "../common/config_utils.hpp"
#include "../common/nexus_utils.hpp"

static const string program_name = "xml2nx";
static const string help_header = 
"Program usage:\n  xml2nx [OPTIONS] INPUT FILES";

int main(int argc,char **argv)
{
    configuration conf = create_config();

    if(argc<2)
    {
        std::cerr<<"Insufficient number of command line arguments!"<<std::endl;
        std::cerr<<"Use xml2nx -h for help  ..."<<std::endl;
        return 1;
    }

    //--------- setup CLI configuration ---------------------------------------
    if(parse_cli_opts(argc,argv,program_name,conf))
        return 1;
   
    if(check_help_request(conf,help_header)) 
        return 1;
  
    try
    {
        //-------------- read the XML data ------------------------------------
        tree::ptree xmltree;
        if(open_xml_file(conf.value<string>("input-file"),xmltree))
            return 1;

        //---------------------------- open the nexus file --------------------

        //get the target file
        nxpath path = path_from_string(conf.value<string>("parent"));
        std::cout<<"output file: "<<path.filename()<<std::endl;
        h5::nxfile file = open_nexus_file(path,conf.value<bool>("append"));
    
        //get the group where to append XML data
        h5::nxgroup target_group = file["/"];
        get_group(target_group,path,target_group,false);
       
        //create the objects below the target group
        create_objects(target_group,xmltree);


        file.close();
    }
    catch(nxfile_error &error)
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
