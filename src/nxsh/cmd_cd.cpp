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
 * Created on: Dec 18, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "cmd_cd.hpp"
#include <boost/tokenizer.hpp>

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/core/config/cli_args.hpp>
#include <pni/core/config/config_parser.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

//-----------------------------------------------------------------------------
void cmd_cd::setup(const std::vector<string> &cargs)
{
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_argument(config_argument<string>("target",-1,"",&_target));
    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());

    if(_config->has_option("help"))
    {
        throw cli_help_request(EXCEPTION_RECORD,"show help");
    }
}

//-----------------------------------------------------------------------------
void cmd_cd::execute(std::unique_ptr<environment> &env)
{
    boost::char_separator<char> separator("/");
    boost::tokenizer<boost::char_separator<char> > t(_target,separator);

    for(auto iter = t.begin();iter!=t.end();++iter)
        env->current_group(*iter);
}

//-----------------------------------------------------------------------------
void cmd_cd::help() const
{
    std::cout<<"cd <target>  - change to new group"<<std::endl;
    std::cout<<*_config<<std::endl;
    
}
