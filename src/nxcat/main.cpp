#include<iostream>
#include<fstream>
#include<list>
#include<vector>

#include<pni/core/types.hpp>
#include<pni/io/nx/nx.hpp>
#include<pni/io/nx/nxobject_type.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include "../common/nx_object_path.hpp"
#include "../common/field_io.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    configuration conf;

    conf.add_argument(config_argument<nx_object_path>("target",1));

    parse(conf,cliargs2vector(argc,argv));

    //obtain the path to the target
    nx_object_path target = conf.value<nx_object_path>("target");

    //need to open the file only in read only mode
    nxfile file = nxfile::open_file(target.filename(),true);
    
    if(target.attribute_name() != "")
    {
        //perform an IO operation on an attribute
        nxattribute attr = file[target.object_path()].attr(target.attribute_name());
        
        std::cout<<attr<<std::endl;
          
    }
    else
    {
        //perform the IO operation on a field
        nxobject obj = file[target.object_path()];
        if(obj.object_type() != pni::io::nx::nxobject_type::NXFIELD)
        {
            //have to throw some exception here
        }

        nxfield field(obj); //create the field for the IO operation
        std::cout<<field<<std::endl; 

    }



    return 0;
}


