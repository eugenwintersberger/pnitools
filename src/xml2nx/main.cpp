#include<iostream>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

#include "xml_utils.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
namespace tree = boost::property_tree;



int main(int argc,char **argv)
{
    NXFile nxfile = NXFile::create_file("test.h5",true,0);

    tree::ptree xmltree; 
    tree::read_xml("test.xml",xmltree);
    
    create_objects(nxfile,xmltree);


    nxfile.close();
    return 0;
}
