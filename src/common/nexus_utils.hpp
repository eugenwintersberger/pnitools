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

using namespace pni::core;
using namespace pni::io::nx;

/*!
\ingroup common_devel
\brief get the object class

Returns the class of an object by returning the value of the NX_class attribute
of an object. Currently this will only return a value if the object is a group
type. However, due to the generallity of the code this could also be a field or
any other type that can hold attributes.
If the object has no attribute NX_class an empty string will be returned.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\return value of NX_class attribute
*/
template<typename OTYPE> string get_class(const OTYPE &o)
{
    string value;
    if(o.has_attr("NX_class"))
        o.attr("NX_class").read(value);

    return value;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief check object class

Returns true if an object is of a particular class. 
\tparam OTYPE object type
\param o reference to instance of OTYPE
\param type type string 
\return true if object class and type are equal
*/
template<typename OTYPE> bool is_class(const OTYPE &o,const string &type)
{
    return get_class(o)==type;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief true if object is group

Return true if an instance of an object is a group type.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\return true if o is a group 
*/
template<typename OTYPE> bool is_group(const OTYPE &o)
{
    return o.object_type()==nxobject_type::NXGROUP;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief true if object is a field

Return true if an instance of an object is a field object.
\tparam OTYPE object type
\param o reference to an instance of OTYPE
\return true of o is a field
*/
template<typename OTYPE> bool is_field(const OTYPE &o)
{
    return o.object_type() == nxobject_type::NXFIELD;
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get unit of a field

Returns the unit of a Nexus field. If the Nexus field has no unit attached to it
an empty string is returned. 
\tparam FTYPE field type
\param f instance of FTYPE
\return string with the unit of the field
*/
template<typename FTYPE>  string get_unit(const FTYPE &f)
{
    string buffer;
    if(f.has_attr("units"))
        f.attr("units").read(buffer);

    return buffer;
}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief split a nexus path

Splits  a given Nexus path in to two parts at  a particular index s.
\param p original path
\param s index where to split 
\param p1 first part of the path
\param p2 second part of the path
*/
void split_path(const nxpath &p,size_t s,nxpath &p1,nxpath &n2);
//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get object by name

Return an object specified by a Nexus path. From the nature of a nexus file we
can assume that every object in the path except the last one has to be a group
as it must hold other objects 
*/
template<typename PTYPE, typename OTYPE>
bool find_object(const PTYPE &p,const nxpath &path,OTYPE &object)
{
    nxpath group_path;
    nxpath target_path;

    split_path(path,path.size()-1,group_path,target_path);

    //try to fetch the groups 
    PTYPE t_group;
    if(!get_group(p,group_path,t_group,false)) return false;

    /*now we need to fetch the target object. This can be either a group or a
     * field - need to take this into account
     */
    //first we try to fetch a group
    if(get_group(t_group,target_path,object)) return true;

    

    return true;
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

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief search for group by class

Search for a child group below p for a group with a particular class name
and return the group if found. The function returs false if not successful
and true otherwise. 

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
        if(is_group(*iter)) continue;

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
        if(is_group(*iter)) continue;

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
    if(!find_group_by_name(p,gname,g))
        return false;

    if(is_class(g,gclass)) return true;

    return false;
}

//-------------------------------------------------------------------------
/*!
\brief common_devel
\brief create a group

Creates a group of type GTYPE below a group of type GTYPE. 

\throws pni::io::nx::nxgroup_error 
\throws pni::io::nx::nxattribute_error
\tparam PTYPE type of parent group
\tparam GTYPE type of target group
\param p parent groupt
\param gname name of the new group
\param gclass class of the new group
\param g target group
*/
template<typename PTYPE,typename GTYPE>
void create_group(const PTYPE &p,const string &gname,const string &gclass,
                  GTYPE &g)
{
    g=p.create_group(gname,gclass);
}

//-----------------------------------------------------------------------------
template<typename PTYPE,typename GTYPE>
void create_group(const PTYPE &p,const string &gname,GTYPE &g)
{
    g=p.create_group(gname);
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
                if(create) create_group(p,name,gclass,g);
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
                if(create) create_group(p,name,g);
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
        get_group(g,element.first,element.second,g,create);
}

//-----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief get an existing field

Return an existing field according to a path object. 
\tparam GTYPE group type
\tparam FTYPE field type
\param p parent group 
\param path the field path relative to the parent
\param f field instance
*/
template<typename GTYPE,typename FTYPE>
void get_field(const GTYPE &p,const nxpath &path,FTYPE &f)
{
    //here we assume that all elements in the path except the last one refer to
    //groups - create a new path with one element less
    nxpath::group_path_t groups(path.size()-1);
    nxpath::group_path_t::const_iterator fielditer = path.begin();
    std::advance(fielditer,path.size()-1);
    std::copy(path.begin(),fielditer,groups.begin());
    nxpath groups_only("",groups,"");

    GTYPE parent; 
    get_group(p,groups_only,parent,false);

    f = parent[fielditer->first];

}

//----------------------------------------------------------------------------
/*!
\ingroup common_devel
\brief create a field

Create a field from a type_id_t and a shape object. 
\throws type_error if data type is not supported
\tparam PTYPE parent type
\tparam FTYPE field type
\tparam STYPE shape type
\param parent instance of PTYPE - there parent object
\param name the name of the new field
\param tid type_id of the field
\param shape instance of STYPE - the shape of the field
\param field reference to the new field
*/
template<typename PTYPE,typename FTYPE,typename STYPE,typename ...FILTERT>
void create_field(const PTYPE &parent,const string &name,type_id_t tid,
                  const STYPE shape,FTYPE &field,FILTERT ...filters)
{
    STYPE cshape(shape.size());
    std::copy(shape.begin(),shape.end(),cshape.begin());
    *cshape.begin() = 1;

    if(tid == type_id_t::UINT8)
        field = parent.create_field<uint8>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT8)
        field = parent.create_field<int8>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT16)
        field = parent.create_field<uint16>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT16)
        field = parent.create_field<int16>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT32)
        field = parent.create_field<uint32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT32)
        field = parent.create_field<int32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::UINT64)
        field = parent.create_field<uint64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::INT64)
        field = parent.create_field<int64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT32)
        field = parent.create_field<float32>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT64)
        field = parent.create_field<float64>(name,shape,cshape,filters...);
    else if(tid == type_id_t::FLOAT128)
        field = parent.create_field<float128>(name,shape,cshape,filters...);
    else
        throw type_error(EXCEPTION_RECORD,
                "Unkown data type!");
}

                  
