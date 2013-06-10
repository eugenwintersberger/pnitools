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
 * Created on: Jun 10, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "xml2nx.hpp"

//-------------------------------------------------------------------------
configuration create_config()
{
    configuration config;

    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("parent","p",
                      "path to the parent object"));
    config.add_option(config_option<bool>("append","a",
                      "append structure to existing file"));
    config.add_argument(config_argument<string>("input_file",-1));

    return config;
}


//------------------------------------------------------------------------
h5::nxfile open_nexus_file(const nxpath &path,bool append)
{

    if(append)
        return  h5::nxfile::open_file(path.filename(),false);
    else
        return h5::nxfile::create_file(path.filename(),false,0);
}
