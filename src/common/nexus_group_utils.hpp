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
and return the group if found. The function returs false if not successful
and true otherwise. This is the case when the group has not been found or
another object which is not a group has been found under this name.

\code
nxgroup g = file["/"];
nxgroup e;

if(!find_group_by_class(g,"NXentry",e))
{
    //no entry found - do something here.
}

\endcode

\tparam PTYPE parent type 
\tparam GTYPE group type
\param p parent group whose childs to search
\param gclass name of the class
\param g resulting group
\return true if group has been found, false otherwise
*/
template<typename PTYPE, typename GTYPE> 
bool find_group_by_class(const PTYPE &p,const string &gclass,GTYPE &g)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //continue the loop if the object is not a group
        if(!is_group(*iter)) continue;

        //here we can do the check
        if(is_class(*iter,gclass)) 
        {
            g = *iter;
            return true;
        }
    }

    return false;
}


//-------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief search for group names

Search for a child group with a particular name. The function returns true
if the search was successful, false otherwise. 
A typical application would look like this:
\code
nxgroup inst = file["/entry/instrument"];
nxgruop detector;
if(!find_group_by_name(inst,"detector_channel_1",detector))
{
    std::cerr<<"Cannot find detector!"<<std::endl;
    return -1;
}
\endcode

\tparam PTYPE parent group type
\tparam GTYPE target group type
\param p parent group 
\param gname name of the group to look for
\param g target group
\return true if group has been found, false otherwise
*/
template<typename PTYPE,typename GTYPE>
bool find_group_by_name(const PTYPE &p,const string &gname,GTYPE &g)
{
    for(auto iter=p.begin();iter!=p.end();++iter)
    {
        //continue with the loop of the object is not a group
        if(!is_group(*iter)) continue;

        //check name
        if(iter->name() == gname) 
        {
            g = *iter;
            return true;
        }
    }

    return false;
}

//-------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief find group by class and name

Find a child group with a particular name and class. If the search succeeds 
the function returns true, false otherwise. 

\tparam PTYPE parent type
\tparam GTYPE target group type
\param p parent instance
\param gname group name
\param gclass class name
\param g target group
\return true if found, false otherwise
*/
template<typename PTYPE,typename GTYPE>
bool find_group_by_name_and_class(const PTYPE &p,const string &gname,
                                  const string &gclass,GTYPE &g)
{
    //ok - if already the name is not correct we do not need to check the class
    if(!find_group_by_name(p,gname,g))
        return false;

    if(is_class(g,gclass)) return true;

    return false;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a group

Creates a group below a parent and returns it to the callee. This flavor of
group creation requires that the parent is already a group type. 
\throws pni::io::nx::nxgroup_error
\throws pni::io::nx::nxattribute_error
\tparam PTYPE parent and group type
\tparam GTYPE group type, by default the same as PTYPE
\param p instance of PTYPE as parent
\param gname name of the new group
\param gclass name of the class the group belongs to
\return instance of PTYPE as the new group
*/
template<typename PTYPE,typename GTYPE = PTYPE>
GTYPE create_group(const PTYPE &p,const string &gname,const string &gclass)
{
    return p.create_group(gname,gclass);
}


//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a group

Create a group and return it to the callee. 
\throws pni::io::nx::nxgroup_error
\tparam PTYPE parent type
\tparam GTYPE group type, by default the same as PTYPE
\param p reference to parent group
\param gname name of the group
\return instance of GTYPE
*/
template<typename PTYPE,typename GTYPE=PTYPE>
GTYPE create_group(const PTYPE &p,const string &gname)
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
\thows group_error in case of errors
\tparam PTYPE parent type
\tparam GTYPE group type
\param p parent group
\param name name of the searched group
\param gclass nexus class of the searched group
\param g reference to the group
\param create true of the group should be created 
*/
template<typename PTYPE,typename GTYPE>
void get_group(const PTYPE &p,const string &name, const string &gclass,
               GTYPE &g,bool create=true)
{
    if(!name.empty())
    {
        //groups can only be created if we at least have a name
        if(!gclass.empty())
        {
            if(!find_group_by_name_and_class(p,name,gclass,g))
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
            if(!find_group_by_name(p,name,g))
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
        if(!find_group_by_class(p,gclass,g))
            throw nxgroup_error(EXCEPTION_RECORD,
                "::group_path_tcannot find group of class "+gclass+"!");
    }
    else
    {
        throw nxgroup_error(EXCEPTION_RECORD,
                "Error retrieving group!");
    }
}



//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get a group

This function  is an extension of the get_group. It walks through a Nexus path
and returns the last group of the path. Non-existing groups are automatically
created if the create flag is set to true. 
\throws nxgroup_error in case of errors
\tparam GTYPE group type
\param p parent group
\param path Nexus path object
\param g resulting group
\param create true if missing elements should be created
*/
template<typename GTYPE>
void get_group(const GTYPE &p,const nxpath &path,GTYPE &g,bool create=true)
{
    g = p;
    for(auto element: path)
    {
        if(element.first == ".") continue;
        if(element.first == "..") 
        {
            g = g.parent();
            continue;
        }

        get_group(g,element.first,element.second,g,create);
    }
}

//-----------------------------------------------------------------------------
template<typename GTYPE> 
GTYPE get_group(const GTYPE &p,const nxpath &path,bool create=true)
{
    GTYPE g; 
    try
    {
        get_group(p,path,g,create);
    }
    catch(nxgroup_error &error)
    {
        error.append(EXCEPTION_RECORD);
        throw error;
    }

    return g;
}
