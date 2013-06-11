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
 * Created on: Jan 16,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "nxcat.hpp"
#include "../common/config_utils.hpp"
#include "../common/nexus_utils.hpp"
#include "../common/array_utils.hpp"


static const string prg_name = "nxcat";
static const string help_hdr = "nxcat usage:";

int main(int argc,char **argv)
{
    //--------------------setup program configuration--------------------------
    configuration conf = create_configuration();

    if(parse_cli_opts(argc,argv,prg_name,conf))
        return 1;

    if(check_help_request(conf,help_hdr))
        return 1;

    try
    {
        //----------------------parse the input data----------------------------
        //get the source string
        nxpath source = path_from_string(conf.value<string>("source"));
        
        //open file in read only mode - the file must obviously exist
        h5::nxfile file = h5::nxfile::open_file(source.filename(),true);
        h5::nxgroup root = file["/"];
        h5::nxfield field; 
        get_field(root,source,field);

        //need to create an array from the data
        auto shape = field.shape<shape_t>();
        array data = create_array(field.type_id(),shape);

        field.read(data);
        for(auto v: data)
            std::cout<<v<<std::endl;
        
            

    }
    catch(nxgroup_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Something went wrong!"<<std::endl;
        return 1;
    }



    return 0;
}


