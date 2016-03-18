//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/algorithms/get_type.hpp>
#include <pni/io/nx/algorithms/get_shape.hpp>
#include <pni/io/nx/algorithms/is_field.hpp>
#include <pni/io/nx/algorithms/is_group.hpp>
#include <pni/io/nx/algorithms/is_attribute.hpp>
#include <pni/io/nx/algorithms/as_link.hpp>
#include <pni/io/nx/algorithms/is_link.hpp>
#include <pni/io/nx/nxlink.hpp>
#include "output.hpp"

#define OTYPE_FIELD_WIDTH 8 
#define DTYPE_FIELD_WIDTH 10
#define STATUS_FIELD_WIDTH 20

string shape_to_string(const shape_t &shape)
{
    std::stringstream ss;

    if(shape.empty()) return string();

    ss<<"(";
    for(auto iter = shape.begin();iter!=shape.end();++iter)
    {
        ss<<*iter;
        if(iter!=shape.end()-1) ss<<",";
    }

    ss<<")";
    return ss.str();

}

//----------------------------------------------------------------------------
//     Implementation of independent functions used in the output class
//----------------------------------------------------------------------------
nxpath trim_path(const nxpath &path,size_t trim_level)
{
    nxpath opath(path);

    for(size_t i=0;i<trim_level;++i) opath.pop_front();

    return opath;
}


//----------------------------------------------------------------------------
string get_data_metadata(const h5::nxobject &o)
{
    std::stringstream ss;

    auto shape = get_shape<shape_t>(o);
    if(shape.empty())
        shape = shape_t{{1}};

    ss<<std::left<<std::setw(DTYPE_FIELD_WIDTH)<<get_type(o)
      <<std::left<<std::setw(STATUS_FIELD_WIDTH)<<shape_to_string(shape);
    return ss.str();
}

//----------------------------------------------------------------------------
string get_field_metadata(const h5::nxobject &o)
{
    std::stringstream ss;
        
    ss<<std::left<<std::setw(OTYPE_FIELD_WIDTH)<<"FIELD"<<get_data_metadata(o);
    return ss.str();
}

//----------------------------------------------------------------------------
string get_group_metadata(const h5::nxobject &o)
{
    std::stringstream ss;
    ss<<std::left<<std::setw(OTYPE_FIELD_WIDTH+DTYPE_FIELD_WIDTH+STATUS_FIELD_WIDTH)
      <<"GROUP";
    return ss.str();
}

//----------------------------------------------------------------------------
string get_attribute_metadata(const h5::nxobject &o)
{
    std::stringstream ss;
    ss<<std::setw(OTYPE_FIELD_WIDTH)<<"ATTRIB\t"<<get_data_metadata(o);
    return ss.str();
}

//----------------------------------------------------------------------------
string get_link_metadata(const h5::nxobject &o)
{
    auto link = as_link(o);
    std::stringstream ss;
    ss<<std::left<<std::setw(OTYPE_FIELD_WIDTH)<<"LINK";

    if(link.type() == nxlink_type::SOFT)
        ss<<std::left<<std::setw(DTYPE_FIELD_WIDTH)<<"INTERNAL";
    else if(link.type() == nxlink_type::EXTERNAL)
        ss<<std::left<<std::setw(DTYPE_FIELD_WIDTH)<<"EXTERNAL";
    
    if(link.status() == nxlink_status::VALID)
        ss<<std::left<<std::setw(STATUS_FIELD_WIDTH)<<"VALID";
    else if(link.status() == nxlink_status::INVALID)
        ss<<std::left<<std::setw(STATUS_FIELD_WIDTH)<<"INVALID";

    return ss.str();

}

//----------------------------------------------------------------------------
string get_metadata(const h5::nxobject &o)
{
    //whatever we get here we first convert it back to nxobject
    h5::nxobject obj(o); 

    if(is_field(obj))          return get_field_metadata(obj);
    else if(is_group(obj))     return get_group_metadata(obj);
    else if(is_attribute(obj)) return get_attribute_metadata(obj);
    else if(is_link(obj))      return get_link_metadata(obj);
    else
        return "";

}

//----------------------------------------------------------------------------
//            Implementation of methods for class output
//----------------------------------------------------------------------------
output::output(std::ostream &stream,const output_config &config):
    _stream(stream),
    _config(config)
{}

//----------------------------------------------------------------------------
void output::write_object(const h5::nxobject &o)
{
    if(_config.long_output()) _stream<<get_metadata(o);

    _stream<<get_path(o);

    if(_config.long_output() && is_link(o))
    {
        auto l = as_link(o);
        _stream<<" -> "<<nxpath::to_string(l.target_path());
    }

    _stream<<std::endl;
        
    //handle attributes
    if(_config.with_attributes())
    {
        //The attribute_manager attribute is only visible for instances 
        //of nxfield and nxgroup. We thus have to convert the child 
        //object to either a field or a group. This is also the reason 
        //why attribute_output is a function template.
        if(is_group(o))
            attribute_output(as_group(o));
        else if(is_field(o))
            attribute_output(as_field(o));
    }
}

//----------------------------------------------------------------------------
string output::get_path(const h5::nxobject &o) const
{
    nxpath p = nxpath::from_string(pni::io::nx::get_path(o));

    return nxpath::to_string(trim_path(p,_config.trim_level()));
}
