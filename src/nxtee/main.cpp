#include <iostream>

#include <pni/core/config/config_parser.hpp>
#include <pni/core/config/configuration.hpp>

#include <pni/io/nx/nx.hpp>

#include "../commong/nx_object_path.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    configuration config;

    config.add_argument(config_argument<nx_object_path>("object-path",-1));
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

    //read data from stdinput
    std::istream input_stream(std::cin);

    while(input_stream

    return 0;
}
