//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ============================================================================
// Created on: Jun 11,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "nxcat.hpp"

configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_argument(config_argument<string_list>("source",-1));
    config.add_option(config_option<bool>("header","",
                      "show header with units",false));
    config.add_option(config_option<size_t>("start","s",
                "first row in output",size_t(0)));
    config.add_option(config_option<size_t>("end","e",
                "last row in output",size_t(0)));
    return config;
}


//-----------------------------------------------------------------------------
column_t read_column(const nxpath &source_path)
{
    //open file in read only mode - the file must obviously exist
    h5::nxfile file = h5::nxfile::open_file(source_path.filename(),true);
    h5::nxobject root = file.root();

    //have to retrieve the object from the file
    auto object = get_object(root,source_path);

    //============need to take care here about a particular bug ===============
    //it seems that get_object does not return attributes attached to the root
    //group. Need to take care about this
    if((get_name(object) == "/")&&(!source_path.attribute().empty()))
    {
        object = get_attribute(object,source_path.attribute());
    }

    //==================end of workaround======================================
        
    //try to get a column type from the Nexus object
    column_t column = column_from_nexus_object(object);

    //get the shape fo the data on the file
    auto file_shape = get_shape<shape_t>(object);
    if(is_attribute(object) && file_shape.size()==0)
    {
        file_shape = shape_t{1}; //in case of a scalar attribute
    }                             

    //construct the shape of a single cell entry - this is typically 
    //an array whose original rank is reduced by 1 dimension
    auto data_shape = file_shape.size() >1 ?
                      shape_t(++file_shape.begin(),file_shape.end()): 
                      shape_t{1} ;

    //create the data array
    array data = make_array(get_type(object),data_shape);

    //create a selection in order to read data from the file
    std::vector<slice> selection(file_shape.begin(),file_shape.end());
    selection[0] = slice(0);

    for(size_t i=0;i<file_shape[0];++i)
    {
        selection[0] = slice(i);
        read(object,data,selection);
        column.push_back(data);
    }

    return column;
}

//-----------------------------------------------------------------------------
table_t  read_table(const sources_list &sources)
{
    table_t t;
    for(auto source: sources) t.push_back(read_column(source));

    return t;
}
