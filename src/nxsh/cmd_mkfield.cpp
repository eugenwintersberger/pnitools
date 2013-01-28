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
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

#include "cmd_mkfield.hpp"
#include "../common/string_utils.hpp"

//-----------------------------------------------------------------------------
void cmd_mkfield::setup(const std::vector<string> &cargs)
{
    //setup configuration
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_option(config_option<string>("type","t","field type","string"));
    _config->add_option(config_option<string>("shape","s","field shape"));
    _config->add_option(config_option<string>("chunk","c","chunk shape"));
    _config->add_argument(config_argument<string>("name",-1));

    //parse use arguments
    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());

    //check for help
    if(_config->has_option("help"))
        throw cli_help_request(EXCEPTION_RECORD,"show help");

}

//-----------------------------------------------------------------------------
void cmd_mkfield::execute(std::unique_ptr<environment> &env)
{
    //need to parse the shape
    shape_t shape,cshape;

    auto type = _config->value<string>("type");
    auto name = _config->value<string>("name");
    const nxgroup &cg = env->current_group();

    //we have three situations: 
    //-> no shape
    //-> only shape
    //-> shape and chunk shape
    if(_config->has_option("shape"))
    {
        auto shape = read_shape<shape_t>(_config->value<string>("shape"));
    
        if(_config->has_option("chunk"))
        {
            auto cshape = read_shape<shape_t>(_config->value<string>("chunk"));
            mkfield(cg,name,type,shape,cshape);
        }
        else
            mkfield(cg,name,type,shape);
    }
    else
        mkfield(cg,name,type);
}

//-----------------------------------------------------------------------------
void cmd_mkfield::help() const
{
    std::cout<<*_config<<std::endl;
}

