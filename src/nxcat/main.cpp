#include<iostream>
#include<fstream>
#include<list>
#include<vector>

#include<pni/core/Types.hpp>
#include<pni/io/nx/NX.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include"../common/nx_object_path.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    configuration conf;

    conf.add_option(config_option<nx_object_path>("target","t",
                "Nexus object to read from or write to"));
    conf.add_argument(config_argument<String>("command",1));
    conf.add_argument(config_
    conf.add_argument(config_argument<String>("source",-1,"--"));

    parse(conf,argc,(const char**)argv);

    //--------------------evaluate the command string--------------------------
    String command = conf.value<String>("command");

    //obtain the path to the target
    nx_object_path target = conf.value<nx_object_path>("target");

    //open the file - if data should be written to the file it will be opened in
    //append mode, otherwise in read only mode
    NXfile file = NXFile::open_file(target.filename(),(command == "write"));
    
    if(target.attribute_name() != "")
    {
        //perform an IO operation on an attribute
        NXAttribute attr = file[target.object_path()].attr(target.attribute_name());
        
        
    }
    else
    {
        //perform the IO operation on a field
        NXObject obj = file[target.object_path()];
        if(obj.object_type() != NXObjectType::NXFIELD)
        {
            //have to throw some exception here
        }

        NXField field(obj); //create the field for the IO operation
        
         


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


