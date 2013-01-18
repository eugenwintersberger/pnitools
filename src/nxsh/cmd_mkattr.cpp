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

#include <pni/core/Types.hpp>
#include <pni/io/nx/NX.hpp>
#include <pni/core/config/cli_args.hpp>
#include <pni/core/config/config_parser.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

#include "cmd_mkattr.hpp"
#include "../common/string_utils.hpp"

//-----------------------------------------------------------------------------
void cmd_mkattr::setup(const std::vector<String> &cargs)
{
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_option(config_option<String>("type","t","attribute type"));
    _config->add_option(config_option<String>("shape","s","attribute shape"));
    _config->add_option(config_option<bool>("overwrite","o",
                "overwrite an attribute if it already exists",false));
    _config->add_option(config_option<String>("name","n",
                "name of the attribute"));
    _config->add_argument(config_argument<String>("parent",-1,
                "attribute parent"));
    
    //parse configuration
    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());

}

//-----------------------------------------------------------------------------
void cmd_mkattr::execute(std::unique_ptr<environment> &env)
{
    //get the parent object
    const NXGroup &cg = env->current_group();
    NXObject o = cg[_config->value<String>("parent")];

    auto type = _config->value<String>("type");
    
    if(_config->has_option("shape"))
        mkattr(o,_config->value<String>("name"),
                 _config->value<String>("type"),
                 read_shape<shape_t>(_config->value<String>("shape")),
                 _config->value<bool>("overwrite"));
    else
        mkattr(o,_config->value<String>("name"),
                 _config->value<String>("type"),
                 _config->value<bool>("overwrite"));

}

//-----------------------------------------------------------------------------
void cmd_mkattr::help() const
{
    std::cout<<*_config<<std::endl;
}
