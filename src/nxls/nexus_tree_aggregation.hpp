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
 * Created on: Jul 18,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <vector>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/nxvariant.hpp>

using namespace pni::core;
using namespace pni::io::nx;

//-----------------------------------------------------------------------------
template<typename OTYPE> void assemble_path(const OTYPE &o,string &path)
{
    if(is_group(o))
    {
        auto group_name = get_name(o);
        auto group_class = get_class(o);

        string element = "/"+group_name;
        if(!group_class.empty()) element+=":"+group_class;

        path = element + path;
    }
    else if(is_field(o))
    {
        //in the case of a field the object is a toplevel of a path
        path = "/"+get_name(o);
    }
    else
        throw type_error(EXCEPTION_RECORD,
                "Object is of unknown type!");

    //recursive call of this function if the parent is not the root group
    auto parent = get_parent(o);
    if(get_name(parent) != "/") assemble_path(parent,path);
}


//-----------------------------------------------------------------------------
template<typename OTYPE,typename CTYPE>
void aggregate_nexus_path(const OTYPE &o,CTYPE &c,bool recursive,bool
        with_attributes)
{
    if(!is_group(o))
        throw type_error(EXCEPTION_RECORD,
                "Object ["+get_name(o)+"] is not a group!");

    for(size_t i=0;i<get_size(o);++i)
    {
        //get a child object
        auto child = get_child(o,i);

        //get the full path of the current child object
        string path;
        assemble_path(child,path);

        //append the path to the container
        c.push_back(path);

        //if the child is a group call this function recursively
        if(is_group(child) && recursive)
            aggregate_nexus_path(child,c,recursive,with_attributes);
    }
}

