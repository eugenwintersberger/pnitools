#include<iostream>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

#include "xml_utils.hpp"
#include "../common/program_config.hpp"
#include "../common/nx_object_path.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
namespace tree = boost::property_tree;



int main(int argc,char **argv)
{
    program_config conf;
    conf.add_option(config_option<nx_object_path>("parent","p",
                "path to the parent object"));
    conf.add_option(config_option<Bool>("append","a",
                "append structure to existing file"));
    conf.add_argument(config_argument<String>("input_file",-1));
   
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
        conf.parse(argc,argv);
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
        tree::read_xml(conf.value<String>("input_file"),xmltree);
    }
    catch(...)
    {
        std::cerr<<"Error reading XML file ";
        std::cerr<<conf.value<String>("input_file")<<"!"<<std::endl;
        return 1;
    }


    //get the target file
    auto opath = conf.value<nx_object_path>("parent");
    NXFile nxfile;
    if(conf.value<Bool>("append"))
    {
        try
        {
            nxfile = NXFile::open_file(opath.filename(),false);
        }
        catch(pni::nx::NXFileError &error)
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
            nxfile = NXFile::create_file(opath.filename(),false,0);
        }
        catch(pni::nx::NXFileError &error)
        {
            std::cerr<<"Error creating file "<<opath.filename();
            std::cerr<<"for writing data!"<<std::endl<<std::endl;
            std::cerr<<error<<std::endl;
            return 1;
        }
    }

    //get the group where to append XML data
    NXGroup target_group = nxfile["/"];
    if(opath.object_path()!="")
    {
        try
        {
            target_group = nxfile[opath.object_path()];
        }
        catch(pni::nx::NXGroupError &error)
        {
            std::cerr<<"Error opening target group ";
            std::cerr<<opath.object_path()<<" to append object!";
            std::cerr<<std::endl<<std::endl;
            return 1;
        }
    }
   
    //create the objects below the target group
    create_objects(target_group,xmltree);


    nxfile.close();
    return 0;
}
