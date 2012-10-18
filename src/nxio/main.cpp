#include<iostream>
#include<list>
#include<vector>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

#include"../common/ProgramConfig.hpp"
#include"../common/NXObjectPath.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

typedef std::vector<String> input_t;

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    ProgramConfig conf;

    conf.add_option(ConfigOption<NXObjectPath>("target","t",
                "Nexus object to read from or write to"));
    conf.add_argument(ConfigArgument<String>("command",1));
    conf.add_argument(ConfigArgument<input_t>("input",-1,input_t{"--"}));

    conf.parse(argc,argv);

    //--------------------evaluate the command string--------------------------
    String command = conf.value<String>("command");
    NXObjectPath target = conf.value<NXObjectPath>("target");
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


