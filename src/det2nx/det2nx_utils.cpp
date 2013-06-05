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
 * Created on: Jun 5,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "det2nx.hpp"

//------------------------------------------------------------------------
configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h",
                "show short help text",false));
    config.add_option(config_option<string>("output","o",
                "output file","output.h5.nx"));
    config.add_option(config_option<string>("nx-path","p",
                "target path","/entry/instrument/detector"));
    config.add_option(config_option<string>("field","f",
                "target field","data"));
    config.add_option(config_option<bool>("append","a",
                "append data to existing field",true));
    config.add_argument(config_argument<strlist>("input-files",-1,strlist{"-"}));
    return config;
}

//-----------------------------------------------------------------------------
nxfile open_output_file(const string &fname)
{
	fs::path output_file_path(config.value<string>("output"));
	if((!fs::exists(output_file_path)))
		//if the file does not already exist we need to create it
        return nxfile::create_file(config.value<string>("output"));
    else
        //open an existing output file
        return nxfile::open_file(config.value<string>("output"));
}

