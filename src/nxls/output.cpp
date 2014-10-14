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

#include "output.hpp"


std::ostream &operator<<(std::ostream &stream,const shape_t &shape)
{
    if(shape.empty())
        return stream;
   
    stream<<"(";
    for(auto iter = shape.begin();iter!=shape.end();++iter)
    {
        stream<<*iter;
        if(iter!=shape.end()-1) stream<<",";
    }

    stream<<")";
    return stream;
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

    //if(shape.empty()) shape = shape_t{{1}};

    ss<<get_type(o)<<'\t'<<shape<<'\t';
    return ss.str();
}

//----------------------------------------------------------------------------
string get_field_metadata(const h5::nxobject &o)
{
    std::stringstream ss;
        
    ss<<"FIELD \t"<<get_data_metadata(o);
    return ss.str();
}

//----------------------------------------------------------------------------
string get_group_metadata(const h5::nxobject &o)
{
    return string("GROUP \t\t\t");
}

//----------------------------------------------------------------------------
string get_attribute_metadata(const h5::nxobject &o)
{
    std::stringstream ss;
    ss<<"ATTRIB\t"<<get_data_metadata(o);
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
string output::get_path(const h5::nxobject &o) const
{
    nxpath p = nxpath::from_string(pni::io::nx::get_path(o));

    return nxpath::to_string(trim_path(p,_config.trim_level()));
}
