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
#include "../common/file.hpp"

//-------------------------------------------------------------------------
configuration create_config()
{
    configuration config;

    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<string>("parent","p",
                      "path to the parent object"));
    config.add_option(config_option<bool>("overwrite","o",
                      "overwrite an eventually existing file",false));
    config.add_argument(config_argument<string>("input-file",-1));

    return config;
}


//------------------------------------------------------------------------
h5::nxfile open_nexus_file(const nxpath &path,bool overwrite)
{
    //have to check if the file existsa
    bool exists = false;
    try
    {
        file f(path.filename());
        exists = true;
    }
    catch(file_error &error)
    {}

    if(overwrite || (!exists))
        //when the overwrite flag is set or the file does not exist we 
        //we simply recreate or create it 
        return h5::nxfile::create_file(path.filename(),true,0);
    else
        //without overwrite the file is opened in append mode
        return h5::nxfile::open_file(path.filename(),false);
}
