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

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/config/cli_args.hpp>
#include <pni/core/config/config_parser.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

#include "cmd_mkattr.hpp"
#include "../common/string_utils.hpp"

//-----------------------------------------------------------------------------
void cmd_mkattr::setup(const std::vector<string> &cargs)
{
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_option(config_option<string>("type","t","attribute type"));
    _config->add_option(config_option<string>("shape","s","attribute shape"));
    _config->add_option(config_option<bool>("overwrite","o",
                "overwrite an attribute if it already exists",false));
    _config->add_option(config_option<string>("name","n",
                "name of the attribute"));
    _config->add_argument(config_argument<string>("parent",-1,
                "attribute parent"));
    
    //parse configuration
    parse(*_config,cargs);

}

//-----------------------------------------------------------------------------
void cmd_mkattr::execute(std::unique_ptr<environment> &env)
{
    //get the parent object
    const nxgroup &cg = env->current_group();
    nxobject o = cg[_config->value<string>("parent")];

    auto type = _config->value<string>("type");
    
    if(_config->has_option("shape"))
        mkattr(o,_config->value<string>("name"),
                 _config->value<string>("type"),
                 read_shape<shape_t>(_config->value<string>("shape")),
                 _config->value<bool>("overwrite"));
    else
        mkattr(o,_config->value<string>("name"),
                 _config->value<string>("type"),
                 _config->value<bool>("overwrite"));

}

//-----------------------------------------------------------------------------
void cmd_mkattr::help() const
{
    std::cout<<*_config<<std::endl;
}
