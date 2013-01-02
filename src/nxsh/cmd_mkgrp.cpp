#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>
#include <pni/utils/config/cli_args.hpp>
#include <pni/utils/config/configuration.hpp>
#include <pni/utils/config/config_parser.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include "cmd_mkgrp.hpp"

//-----------------------------------------------------------------------------
void cmd_mkgrp::setup(const std::vector<String> &cargs)
{
    configuration config;
    config.add_option(config_option<String>("class","c","group class","",
                                            &_class));
    config.add_argument(config_argument<String>("name",-1,"", &_name));

    cli_args args(cargs);
    parse(config,args.argc(),args.argv());
}

//-----------------------------------------------------------------------------
void cmd_mkgrp::execute(std::unique_ptr<environment> &env)
{
    const NXGroup &cg = env->current_group();
  
    //if no group name was passed - do nothing
    if(_name.empty()) return;

    //create the group
    if(_class.empty())
        cg.create_group(_name);
    else
        cg.create_group(_name,_class);
}

