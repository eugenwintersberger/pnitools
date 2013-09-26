/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Oct 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include<sstream>
#include<pni/core/types.hpp>
#include<pni/io/nx/nx.hpp>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>

#include "../common/string_utils.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

using namespace pni::core;
using namespace pni::io::nx;
namespace tree = boost::property_tree;

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief open the xml file

Open the XML file. If the operation was successful the function returns false. 
In case of errors true is returned.
\param fname name of the file
\param tree reference to the tree
\return true in case of errors, false otherwise
*/
bool open_xml_file(const string &fname,tree::ptree &tree);

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create shape form dimensions tag

Create a shape container from the dimensions tag in the XML file. 
\param dims ptree instance to the dimensions tag
\return instance of shape_t with the shapea
*/
shape_t dimensions2shape(const tree::ptree &dims);

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create a field from xml data

Create a field from the information provided by the XML file. 
\tparam PTYPE parent type
\param parent instance of PTYPE - the parent of the field
\param name the fields name
\param tc type code 
\param s shape of the field
\return instance of NXField
*/
template<typename PTYPE>
h5::nxfield create_field(const PTYPE &parent,const string &name,
                     const string &tc,const shape_t &s)
{
    if(tc == "uint8")
        return parent.template create_field<uint8>(name,s);
    if(tc == "int8")
        return parent.template create_field<int8>(name,s);
    if(tc == "uint16")
        return parent.template create_field<uint16>(name,s);
    if(tc == "int16")
        return parent.template create_field<int16>(name,s);
    if(tc == "uint32")
        return parent.template create_field<uint32>(name,s);
    if(tc == "int32")
        return parent.template create_field<int32>(name,s);
    if(tc == "uint64")
        return parent.template create_field<uint64>(name,s);
    if(tc == "int64")
        return parent.template create_field<int64>(name,s);
    if(tc == "float32")
        return parent.template create_field<float32>(name,s);
    if(tc == "float64")
        return parent.template create_field<float64>(name,s);
    if(tc == "float128")
        return parent.template create_field<float128>(name,s);
    if(tc == "complex32")
        return parent.template create_field<complex32>(name,s);
    if(tc == "complex64")
        return parent.template create_field<complex64>(name,s);
    if(tc == "complex128")
        return parent.template create_field<complex128>(name,s);
    if(tc == "bool")
        return parent.template create_field<bool>(name,s);
    if(tc == "binary")
        return parent.template create_field<binary>(name,s);
    if(tc == "string")
        return parent.template create_field<string>(name,s);

    std::stringstream ss;
    ss<<"Error creating field - type code "<<tc<<" is not supported!";
    throw nxfield_error(EXCEPTION_RECORD,ss.str());

    return h5::nxfield(); //just to make the compiler happy
}

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create a attribute from xml data

Create an attribute at a parent as descriped by the xml definition. Attributes
actually can only be scalar - so we will stick to this convention.
\tparam PTYPE parent type
\param parent instance of PTYPE - the parent of the field
\param name the fields name
\param tc type code 
\return instance of NXField
*/
template<typename PTYPE>
h5::nxfield create_attribute(const PTYPE &parent,const string &name,
                     const string &tc,const shape_t &s)
{
    if(tc == "uint8") return parent.template attr<uint8>(name);
    if(tc == "int8")  return parent.template attr<int8>(name);
    if(tc == "uint16") return parent.template attr<uint16>(name);
    if(tc == "int16")  return parent.template attr<int16>(name);
    if(tc == "uint32") return parent.template attr<uint32>(name);
    if(tc == "int32")  return parent.template attr<int32>(name);
    if(tc == "uint64") return parent.template attr<uint64>(name);
    if(tc == "int64")  return parent.template attr<int64>(name);
    if(tc == "float32") return parent.template attr<float32>(name);
    if(tc == "float64") return parent.template attr<float64>(name);
    if(tc == "float128") return parent.template attr<float128>(name);
    if(tc == "complex32") return parent.template attr<complex32>(name);
    if(tc == "complex64") return parent.template attr<complex64>(name);
    if(tc == "complex128") return parent.template attr<complex128>(name);
    if(tc == "bool") return parent.template attr<bool>(name);
    if(tc == "binary") return parent.template attr<binary>(name);
    if(tc == "string") return parent.template attr<string>(name);

    std::stringstream ss;
    ss<<"Error creating attribute - type code "<<tc<<" is not supported!";
    throw nxattribute_error(EXCEPTION_RECORD,ss.str());

    return h5::nxattribute(); //just to make the compiler happy
}
//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief write static data from XML

Write data from XML file to the Nexus file. The target object can be either a
field or an attribute.
\param tag the actual tag whose data shall be written
\param field the field where to write the data
*/
template<typename WTYPE>
void write_data(const tree::ptree &tag,const WTYPE &object)
{
    type_id_t tid = object.type_id();

    if(tid == type_id_t::UINT8) object.write(tag.get_value<uint8>());
    else if(tid == type_id_t::INT8) object.write(tag.get_value<int8>());
    else if(tid == type_id_t::UINT16) object.write(tag.get_value<uint16>());
    else if(tid == type_id_t::INT16) object.write(tag.get_value<int16>());
    else if(tid == type_id_t::UINT32) object.write(tag.get_value<uint32>());
    else if(tid == type_id_t::INT32) object.write(tag.get_value<int32>());
    else if(tid == type_id_t::UINT64) object.write(tag.get_value<uint32>());
    else if(tid == type_id_t::INT64) object.write(tag.get_value<int64>());
    else if(tid == type_id_t::FLOAT32) object.write(tag.get_value<float32>());
    else if(tid == type_id_t::FLOAT64) object.write(tag.get_value<float64>());
    else if(tid == type_id_t::FLOAT128) object.write(tag.get_value<float128>());
    else if(tid == type_id_t::COMPLEX32) object.write(tag.get_value<complex32>());
    else if(tid == type_id_t::COMPLEX64) object.write(tag.get_value<complex64>());
    else if(tid == type_id_t::COMPLEX128) object.write(tag.get_value<complex128>());
    else if(tid == type_id_t::BOOL) object.write(tag.get_value<bool>());
    else if(tid == type_id_t::STRING) object.write(trim(tag.get_value<string>()));
}

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create objects from XML

Recursively creates the objects as described in the XML file below parent.
\tparam PTYPE parent type
\param parent instance of PTYPE
\param t ptree instance with the XML data
*/
template<typename PTYPE>
void create_objects(const PTYPE &parent,tree::ptree &t)
{
#ifdef NOFOREACH
    BOOST_FOREACH(auto child,t)
#else
    for(auto child: t)
#endif
    {
        if(child.first == "group")
        {
            //create the group and call the function recursively
            auto name = child.second.template get<string>("<xmlattr>.name");
            auto type = child.second.template get<string>("<xmlattr>.type");

            h5::nxgroup g = parent.create_group(name,type);
            create_objects(g,child.second);

        }
        else if(child.first == "field")
        {
            auto name = child.second.template get<string>("<xmlattr>.name");
            auto type = child.second.template get<string>("<xmlattr>.type");

            shape_t shape;
            //obtain the shape
            tree::ptree dim_node;
            try
            {
                tree::ptree dim_node = child.second.get_child("dimensions");
                shape = dimensions2shape(dim_node);
            }
            catch(...)
            {}

            //create the field
            h5::nxfield f = create_field(parent,name,type,shape);

            //------------------try to write units attribute--------------------
            try
            {
                auto units = child.second.template get<string>("<xmlattr>.units");
                f.attr<string>("units").write(units);
            }
            catch(...)
            {}

            //-------------------try to write long_name attribute--------------
            try
            {
                auto lname = child.second.template get<string>("<xmlattr>.long_name");
                f.attr<string>("long_name").write(lname);
            }
            catch(...)
            {}

            //--------------------now we can try to write default data---------
            try
            {
                write_data(child.second,f);
            }
            catch(...)
            {}

          

        }
        else if(child.first == "attribute")
        {
            auto name = child.second.template get<string>("<xmlattr>.name");
            auto type = child.second.template get<string>("<xmlattr>.type");

            h5::nxattribute a = create_attribute(parent,name,type);

            //try to write some data
            write_data(child.second,a);

        }
        else if(child.first == "link")
        {
            auto name = child.second.template get<string>("<xmlattr>.name");
            auto target = child.second.template get<string>("<xmlattr>.target");
            parent.link(name,target);
        }
    }
}
