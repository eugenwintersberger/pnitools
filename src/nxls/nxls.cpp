//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
// Created on: 30.06.2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include "nxls.hpp"
#include "config.hpp"
#include <pni/io/nx/flat_group.hpp>

template<typename OTYPE>
void attribute_output(const OTYPE &parent)
{
    for(auto attribute: parent.attributes)
        std::cout<<get_path(attribute)<<std::endl;
}

template<typename OTYPE> 
void output(const OTYPE &parent,bool with_attributes)
{
    for(auto child: parent) 
    {
        std::cout<<get_path(child)<<std::endl;
        if(with_attributes)
        {
            if(is_group(child))
                attribute_output(as_group(child));
            else if(is_field(child))
                attribute_output(as_field(child));
        }

    }
}


int main(int argc,char **argv)
{
    //create configuration
    configuration config = get_config(argc,argv);

    try
    {
        nxpath path = nxpath::from_string(config.value<string>("nxpath"));
        h5::nxfile file = h5::nxfile::open_file(path.filename(),true);
        h5::nxobject root = file.root();

        //get the root object from where to start
        if(path.size())
            root = get_object(root,path);

        if(config.value<bool>("recursive"))
            output(make_flat(root),config.value<bool>("show-attributes"));
        else
            output(h5::nxgroup(root),config.value<bool>("show-attributes"));

    }
    catch(pni::core::index_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::io::object_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }


	return 0;
}

