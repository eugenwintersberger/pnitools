#include<iostream>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;
namespace tree = boost::property_tree;

template<typename PTYPE>
void create_groups(const PTYPE &parent,tree::ptree &t)
{
    for(auto child: t)
    {
        if(child.first == "group")
        {
            //create the group and call the function recursively
            auto name = child.second.template get<String>("<xmlattr>.name");
            auto type = child.second.template get<String>("<xmlattr>.type");
            NXGroup g = parent.create_group(name,type);
            create_groups(g,child.second);

        }
        else if(child.first == "field")
        {

        }
    }
}

int main(int argc,char **argv)
{
    NXFile nxfile = NXFile::create_file("test.h5",true,0);

    tree::ptree xmltree; 
    tree::read_xml("test.xml",xmltree);

    
    create_groups(nxfile,xmltree);


    nxfile.close();
    return 0;
}
