#include<iostream>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

#include "xml_utils.hpp"
#include "../common/ProgramConfig.hpp"
#include "../common/NXObjectPath.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
namespace tree = boost::property_tree;



int main(int argc,char **argv)
{
    ProgramConfig conf;
    conf.add_option(ConfigOption<NXObjectPath>("parent","p",
                "path to the parent object"));
    conf.add_option(ConfigOption<Bool>("append","a",
                "append structure to existing file"));
    conf.add_argument(ConfigArgument<String>("input_file",-1));
   
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
    catch(CLIHelpRequest &error)
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }

    //get the target file
    auto opath = conf.value<NXObjectPath>("parent");
    NXFile nxfile;
    if(conf.value<Bool>("append"))
        nxfile = NXFile::open_file(opath.filename(),false);
    else
        nxfile = NXFile::create_file(opath.filename(),false,0);

    //get the group where to append XML data
    NXGroup target_group = nxfile["/"];
    if(opath.object_path()!="")
        target_group = nxfile[opath.object_path()];

    //read the XML data 
    tree::ptree xmltree; 
    tree::read_xml("test.xml",xmltree);
   
    //create the objects below the target group
    create_objects(target_group,xmltree);


    nxfile.close();
    return 0;
}
