#include<iostream>
#include<list>
#include<vector>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include <pni/utils/config/configuration.hpp>
#include <pni/utils/config/config_parser.hpp>
#include"../common/nx_object_path.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

typedef std::vector<String> input_t;

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    configuration conf;

    conf.add_option(config_option<nx_object_path>("target","t",
                "Nexus object to read from or write to"));
    conf.add_argument(config_argument<String>("command",1));
    conf.add_argument(config_argument<input_t>("input",-1,input_t{"--"}));

    parse(conf,argc,(const char**)argv);

    //--------------------evaluate the command string--------------------------
    String command = conf.value<String>("command");

    nx_object_path target = conf.value<nx_object_path>("target");
    if(command == "read")
    {
        //open the file in read only mode
        NXFile file = NXFile::open_file(target.filename(),true);

        if(target.attribute_name() != "")
        {
            //we want to read an attribute
            NXAttribute attr =
                file[target.object_path()].attr(target.attribute_name());


        }

    }
    else if(command == "write")
    {
        input_t ilist = conf.value<input_t>("input");
        for(auto v: ilist)
            std::cout<<v<<" ";

        std::cout<<std::endl;
    }
    else 
    {
        std::cerr<<"Unknown command - aborting!"<<std::endl;
        return 1;
    }



    return 0;
}


