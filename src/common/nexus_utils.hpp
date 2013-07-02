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
 * Created on: Jun 7, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

#include "nexus_object_utils.hpp"
#include "nexus_path_utils.hpp"
#include "nexus_group_utils.hpp"
#include "nexus_field_utils.hpp"
#include "nxvariant_traits.hpp"
#include "get_parent.hpp"
#include "get_attribute.hpp"

using namespace pni::core;
using namespace pni::io::nx;


//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get object by name

Return an object specified by a Nexus path. From the nature of a nexus file we
can assume that every object in the path except the last one has to be a group
as it must hold other objects 
*/
template<typename VTYPE> 
typename nxvariant_traits<typename nxvariant_member_type<VTYPE,0>::type>::object_types 
get_object(const VTYPE &p,const nxpath &path)
{
    typedef typename nxvariant_member_type<VTYPE,0>::type first_type;
    typedef typename nxvariant_traits<first_type>::object_types object_types;
    nxpath group_path;
    nxpath target_path;
    object_types result;

    split_last(path,group_path,target_path);

    //loop over all parent groups
    object_types parent = p;
    for(auto element: group_path)
    {
        if(element.first == ".") continue;
        if(element.first == "..")
        {
            parent = get_parent(parent);
            continue;
        }

        parent = get_child(parent,element.first,element.second);
    }

    //having obtained the parent object we have to look now into it
    result = get_child(parent,target_path.begin()->first,
                              target_path.begin()->second);

    if(!target_path.attribute().empty())
        result = get_attribute(result,target_path.attribute());

    return result;
}

//-----------------------------------------------------------------------------
template<typename PTYPE,typename OTYPE>
bool find_object_by_name(const PTYPE &p,const string &name,OTYPE &o)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //check name
        if(iter->name() == name) 
        {
            o = *iter;
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
template<typename PTYPE,typename OTYPE>
bool find_object_by_class(const PTYPE &p,const string &oclass,OTYPE &o)
{

    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        if(is_class(*iter,oclass))
        {
            o = *iter;
            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
template<typename PTYPE,typename OTYPE>
bool find_object_by_name_and_class(const PTYPE &p,const string &name,
                                   const string &oclass,OTYPE &o)
{
    if(!find_object_by_name(p,name,o))
        return false;

    if(!is_class(o,oclass)) return false;

    return true;
}


