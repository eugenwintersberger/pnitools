/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jan 04, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/utils/config/cli_args.hpp>
#include <pni/utils/config/config_parser.hpp>
#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include "cmd_mkfile.hpp"

//-----------------------------------------------------------------------------
void cmd_mkfile::setup(const std::vector<String> &cargs)
{
    _config = std::unique_ptr<configuration>(new configuration);
    _config->add_option(config_option<bool>("open","o",
                "open file after creation",false));
    _config->add_option(config_option<bool>("overwrite","",
                "overwrite a file if it exists",false));
    _config->add_argument(config_argument<String>("name",-1,"file name"));
    
    cli_args args(cargs);
    parse(*_config,args.argc(),args.argv());
}

//-----------------------------------------------------------------------------
void cmd_mkfile::execute(std::unique_ptr<environment> &env)
{
    NXFile file = NXFile::create_file(_config->value<String>("name"),
                                      _config->value<bool>("overwrite"),0);

    if(_config->value<bool>("open"))
        env = std::unique_ptr<environment>(new environment(file));
}

//-----------------------------------------------------------------------------
void cmd_mkfile::help() const
{
    std::cout<<*_config<<std::endl;
}

