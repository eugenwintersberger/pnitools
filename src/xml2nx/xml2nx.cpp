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
// Created on: Oct 17, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include "xml2nx.hpp"
#include "../common/config_utils.hpp"

static const string program_name = "xml2nx";
static const string help_header = 
"Program usage:\n  xml2nx [OPTIONS] INPUT FILES";

class write_predicates
{
    public:
        virtual bool operator()(const h5::nxobject &o) const = 0;
};

struct write_scalars : public write_predicates
{
    public:
        virtual bool operator()(const h5::nxobject &o) const
        {
            if(is_attribute(o) || is_field(o))
                return get_size(o) == 1;

            return false;
        }
};

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
        //-------------- read the XML data ------------------------------------
        xml::node root_node;
        if(!conf.has_option("input-file"))
        {
            //read input data from a stream
            string buffer;
            char value;
            while(std::cin.get(value)) buffer += value;

            root_node = xml::create_from_string(buffer);
        }
        else
        {
            //read data from a file
            auto filename = conf.value<string>("input-file");
            root_node = xml::create_from_file(filename);
        }

        //---------------------------- open the nexus file --------------------

        //get parent path
        nxpath path = nxpath::from_string(conf.value<string>("parent"));

        //obtain the file for the parent
        h5::nxfile file = open_nexus_file(path,conf.value<bool>("overwrite"));
        h5::nxobject parent_group = file.root();

        if(path.size()!=0) 
            //get the group where to append XML data
            parent_group = get_object(parent_group,path);


        //create the objects below the target group
        xml::xml_to_nexus(root_node,parent_group,write_scalars());


        file.close();
    }
    catch(const pni::core::cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::io::parser_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Unkown error!"<<std::endl;
        return 1;
    }
    return 0;
}
