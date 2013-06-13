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
 * Created on: Jun 11,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "nxcat.hpp"
#include "../common/nexus_utils.hpp"
#include "../common/array_utils.hpp"

configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_argument(config_argument<string_list>("source",-1));
    config.add_option(config_option<bool>("header","",
                      "show header with units",false));
    config.add_option(config_option<size_t>("start","s",
                "start index for data",size_t(0)));
    config.add_option(config_option<size_t>("end","e",
                "end index for data",size_t(0)));
    return config;
}

//-----------------------------------------------------------------------------
array read_source(const nxpath &source_path)
{
    //open file in read only mode - the file must obviously exist
    h5::nxfile file = h5::nxfile::open_file(source_path.filename(),true);
    h5::nxgroup root = file["/"];
    h5::nxfield field; 
    get_field(root,source_path,field);

    //need to create an array from the data
    auto shape = field.shape<shape_t>();
    array data = create_array(field.type_id(),shape);
    field.read(data);

    return data;
}
