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
column_t read_column(const nxpath &source_path)
{
    //open file in read only mode - the file must obviously exist
    h5::nxfile file = h5::nxfile::open_file(source_path.filename(),true);
    h5::nxgroup root = file["/"];
    h5::nxfield field; 
    get_field(root,source_path,field);
    
    //prepear the column
    column_t column;
    column.name(field.path());
    column.unit(get_unit(field));

    //need to create an array from the data
    auto field_shape = field.shape<shape_t>();
    shape_t array_shape{1};
    if(field_shape.size() != 1)
    {
        array_shape = shape_t(field_shape.size()-1);
        std::copy(field_shape.begin()+1,field_shape.end(),array_shape.begin());
    }
    array data = create_array(field.type_id(),array_shape);

    std::vector<slice> selection;
    selection.push_back(slice(0));
    for(auto d: array_shape)
        selection.push_back(slice(0,d));

    for(size_t i=0;i<field_shape[0];++i)
    {
        selection[0] = slice(i);
        field(selection).read(data);
        column.push_back(data);
    }

    return column;
}

//-----------------------------------------------------------------------------
table_t  read_table(const sources_list &sources)
{
    table_t t;
    for(auto source: sources)
    {
        column_t c = read_column(source);
        t.insert(c.name(),c);
    }

    return t;
}
