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
\brief write static data from XML

Write data from XML file to the Nexus file.
\param tag the actual tag whose data shall be written
\param field the field where to write the data
*/
void write_field(const tree::ptree &tag,const h5::nxfield &field);

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
    for(auto child: t)
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
                write_field(child.second,f);
            }
            catch(...)
            {}

          

        }
        else if(child.first == "link")
        {
            auto name = child.second.template get<string>("<xmlattr>.name");
            auto target = child.second.template get<string>("<xmlattr>.target");
            parent.link(name,target);
        }
    }
}
