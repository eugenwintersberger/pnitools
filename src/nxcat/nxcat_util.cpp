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

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

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
    typedef nxvariant_traits<h5::nxfile>::object_types object_types;
    //open file in read only mode - the file must obviously exist
    h5::nxfile file = h5::nxfile::open_file(source_path.filename(),true);
    object_types root = h5::nxgroup(file["/"]);

    //have to retrieve the object from the file
    auto object = get_object(root,source_path);
        
    //try to get a column type from the Nexus object
    column_t column = column_from_nexus_object(object);

    //need to create an array from the data
    array data = array_from_nexus_object(object);

    if(is_field(object))
    {
        std::vector<slice> selection;
        selection.push_back(slice(0));
        auto array_shape = data.shape<shape_t>();
        auto field_shape = get_shape<shape_t>(object);

        if(get_rank(object)>1)
        {
            //if the original object is not scalar we have to extend the
            //selection by the array shape - otherwise we can leave it as it is
#ifdef NOFOREACH
            BOOST_FOREACH(auto d,array_shape)
#else
            for(auto d: array_shape)
#endif
                selection.push_back(slice(0,d));
        }

        for(size_t i=0;i<field_shape[0];++i)
        {
            selection[0] = slice(i);
            read(object,data,selection);
            column.push_back(data);
        }
    }
    else if(is_attribute(object))
    {
        read(object,data);
        column.push_back(data);
    }

    return column;
}

//-----------------------------------------------------------------------------
table_t  read_table(const sources_list &sources)
{
    table_t t;
#ifdef NOFOREACH
    BOOST_FOREACH(auto source,sources)
#else
    for(auto source: sources)
#endif
    {
        t.push_back(read_column(source));
    }

    return t;
}
