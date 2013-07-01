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
 * Created on: Jun 27, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

#include "nexus_object_utils.hpp"
#include "nexus_path_utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;

/*!
\ingroup common_devel
\brief search for group by class

Search for a child group below p for a group with a particular class name
and return the group if found. If the group is not found an invalid group is
returned. Using the is_valid() function a simple check can be made if the search
was successful. 

A typicall application would look like this
\code
nxgroup g = file["/"];
nxgroup e;

if(!is_valid(e = find_group_by_class(g,"NXentry")))
{
    //no entry found - do something here.
}

\endcode

\tparam GTYPE group type
\param p parent group whose childs to search
\param gclass name of the class
\return an instance of GTYPE
\sa find_group_by_name,find_group_by_name_and_class
*/
template<typename GTYPE> 
GTYPE find_group_by_class(const GTYPE &p,const string &gclass)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //check if the current object is a group and if not continue with the
        //next child
        if(!is_group(*iter)) continue;

        //here we can do the check
        if(is_class(*iter,gclass)) return GTYPE(*iter);
    }

    return GTYPE();
}


//-------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief search for group names

Search for a child group with a particular name. The function returns a valid
group object if the requested group has been found, an invalid object otherwise.
A typical application would look like this:
\code
nxgroup inst = file["/entry/instrument"];
nxgroup detector;
if(!is_valid(detector=find_group_by_name(inst,"detector_channel_1")))
{
    std::cerr<<"Cannot find detector!"<<std::endl;
    return -1;
}
\endcode

\tparam GTYPE target group type
\param p parent group 
\param gname name of the group to look for
\return instance of GTYPE
\sa find_group_by_class,find_group_by_name_and_class
*/
template<typename GTYPE>
GTYPE find_group_by_name(const GTYPE &p,const string &gname)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //continue with the loop of the object is not a group
        if(!is_group(*iter)) continue;

        //check name
        if(iter->name() == gname) return GTYPE(*iter);
    }

    return GTYPE();
}

//-------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief find group by class and name

Find a child group with a particular name and class. If the search succeeds 
a valid group object is returned, an invalid object otherwise.
The function can be used as find_group_by_name or find_group_by_class
\code{.cpp}
nxgroup root = file["/"];
nxgroup entry;

if(!is_valid(entry = find_group_by_name_and_class(root,"entry","NXentry")))
{
    std::cerr<<"Cannot find entry group of the Nexus file!"<<std::endl;
    return -1;
}
\endcode

\tparam GTYPE target group type
\param p parent instance
\param gname group name
\param gclass class name
\return true if found, false otherwise
\sa find_group_by_name,find_group_by_class
*/
template<typename GTYPE>
GTYPE find_group_by_name_and_class(const GTYPE &p,const string &gname,
                                  const string &gclass)
{
    GTYPE g;
    //ok - if already the name is not correct we do not need to check the class
    if(!is_valid(g=find_group_by_name(p,gname))) return GTYPE();

    if(is_class(g,gclass)) return g;

    return GTYPE();
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a group

Creates a group below a parent and returns it to the callee.  

\code{.cpp}
nxgroup root = file["/"];
nxgroup entry;

try
{
    entry = create_group(root,"entry","NXentry");
}
catch(nxgroup_error &error)
{
    ...............
}
catch(nxattribute_error &error)
{
    ...............
}
\endcode

\throws pni::io::nx::nxgroup_error
\throws pni::io::nx::nxattribute_error
\tparam GTYPE group type
\param p instance of GTYPE 
\param gname name of the new group
\param gclass name of the class the group belongs to
\return instance of GTYPE
\sa create_group(p,gname)
*/
template<typename GTYPE>
GTYPE create_group(const GTYPE &p,const string &gname,const string &gclass)
{
    return p.create_group(gname,gclass);
}


//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a group

Create a group and return it to the callee. In this case only the name of the
group is required. This function should generally not be used as each Nexus
group should belong to a particular class. However in some rare cases this might
be not the case. 

\code{.cpp}
nxgroup root = file["/"];
nxgroup log;

try
{
    entry = create_group(root,"log");
}
catch(nxgroup_error &error)
{
    ...................
}
catch(nxattribute_error &error)
{
    ...................
}
\endcode


\throws pni::io::nx::nxgroup_error
\tparam GTYPE group type
\param p reference to parent group
\param gname name of the group
\return instance of GTYPE
*/
template<typename GTYPE>
GTYPE create_group(const GTYPE &p,const string &gname)
{
    return p.create_group(gname);
}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get a group

Check if a group exists below a parent group and return it. The function handles
several special cases. If the group does not exist it will be created as long as
at least its name is given and the create flag is set to true. If the groups
name is an empty string one can still search for the group by its Nexus class.
However, if the function cannot find a group of appropriate class it throws an
exception.
\thows nxgroup_error in case of errors
\tparam PTYPE parent type
\tparam GTYPE group type
\param p parent group
\param name name of the searched group
\param gclass nexus class of the searched group
\param create true of the group should be created 
\return instance of GTYPE 
*/
template<typename GTYPE>
GTYPE get_group(const GTYPE &p,const string &name, const string &gclass,
                bool create=true)
{
    GTYPE g;
    if(!name.empty())
    {
        //groups can only be created if we at least have a name
        if(!gclass.empty())
        {
            if(!is_valid(g = find_group_by_name_and_class(p,name,gclass)))
            {
                //if group not found - either create it or throw an exception
                if(create) g = create_group(p,name,gclass);
                else
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "("+name+":"+gclass+"does not exist!");
            }
        }
        else
        {
            if(!is_valid(g = find_group_by_name(p,name)))
            {
                //if group not found - either create it or throw an exception
                if(create) g = create_group(p,name);
                else
                    throw nxgroup_error(EXCEPTION_RECORD,
                            "("+name+":"+gclass+"does not exist!");
            }
        }
    }
    else if(!gclass.empty())
    {
        if(!is_valid(g = find_group_by_class(p,gclass)))
            throw nxgroup_error(EXCEPTION_RECORD,
                "::group_path_tcannot find group of class "+gclass+"!");
    }
    else
    {
        throw nxgroup_error(EXCEPTION_RECORD,
                "Error retrieving group!");
    }

    return g;
}


//-----------------------------------------------------------------------------
template<typename GTYPE> 
GTYPE get_group(const GTYPE &p,const nxpath &path,bool create=true)
{
    GTYPE g = p; //this is still a problem: 
                   
    for(auto eiter = path.begin(); eiter!=path.end();++eiter)
    {
        if(eiter->first == ".") continue;
        if(eiter->first == "..") 
        {
            g = g.parent();
            continue;
        }

        g = get_group(g,eiter->first,eiter->second,create);
    }

    return g;
}
