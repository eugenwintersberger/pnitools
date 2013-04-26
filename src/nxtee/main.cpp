#include <iostream>
#include <fstream>

#include <pni/core/config/config_parser.hpp>
#include <pni/core/config/configuration.hpp>

#include <pni/io/nx/nx.hpp>

#include "../common/nx_object_path.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

template<typename STREAMT> void read_stream(STREAMT &stream)
{
    while(!stream.eof())
    {
        string buffer;
        stream>>buffer;
        std::cout<<buffer;
    }
}

int main(int argc,char **argv)
{
    configuration config;

    config.add_argument(config_argument<nx_object_path>("object-path",-1));
    config.add_option(config_option<string>("input","i","input file",""));
    config.add_option(config_option<string>("comment","c","comment sign",""));
    config.add_option(config_option<string>("delimiter","d","column delimiter"," "));
    config.add_option(config_option<bool>("help","h","show help",false));

    parse(config,cliargs2vector(argc,argv));

    if(config.value<bool>("help"))
    {
        std::cerr<<"nxtee - stream data from std::in"<<std::endl;
        std::cerr<<"Streams data from std::in to a Nexus object"<<std::endl;
        std::cerr<<std::endl;
        std::cerr<<config<<std::endl;

        return 1;
    }
    
    if(config.value<string>("input")!="")
    {
        //open data file
        std::ifstream input_stream(config.value<string>("input")); 
        read_stream(input_stream);
    }
    else
        read_stream(std::cin);



    return 0;
}
