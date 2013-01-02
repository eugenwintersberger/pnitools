/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jan 02, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

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

