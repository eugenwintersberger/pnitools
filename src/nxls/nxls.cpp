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
//

#include "config.hpp"
#include "utils.hpp"
#include "output_config.hpp"
#include <iostream>
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/flat_group.hpp>

using namespace pni::core;
using namespace pni::io::nx;

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
nxpath trim_path(const nxpath &path,size_t trim_level)
{
    nxpath opath(path);

    for(size_t i=0;i<trim_level;++i) opath.pop_front();

    return opath;
}

//----------------------------------------------------------------------------
template<typename OTYPE>
string get_path(const OTYPE &o,const output_config &config)
{
    nxpath p = nxpath::from_string(get_path(o));

    return nxpath::to_string(trim_path(p,config.trim_level()));
}

//----------------------------------------------------------------------------
string get_data_metadata(const h5::nxobject &o)
{
    std::stringstream ss;

    ss<<get_type(o)<<'\t'<<get_shape<shape_t>(o)<<'\t';
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
template<typename OTYPE>
string get_metadata(const OTYPE &o)
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
template<typename OTYPE>
void attribute_output(const OTYPE &parent,const output_config &config)
{
    for(auto attribute: parent.attributes)
    {
        if(config.long_output()) std::cout<<get_metadata(attribute);

        std::cout<<get_path(attribute,config)<<std::endl;
    }
}

//----------------------------------------------------------------------------
template<typename OTYPE> 
void output(const OTYPE &parent,const output_config &config)
{
    for(auto child: parent) 
    {
        if(config.long_output())
            std::cout<<get_metadata(child);

        std::cout<<get_path(child,config)<<std::endl;
        if(config.with_attributes())
        {
            if(is_group(child))
                attribute_output(as_group(child),config);
            else if(is_field(child))
                attribute_output(as_field(child),config);
        }

    }
}



int main(int argc,char **argv)
{
    //create configuration
    configuration config = get_config(argc,argv);

    nxpath path = get_path(config);

    h5::nxfile file = get_file(path);

    h5::nxobject root = get_root(file,path);

    output_config ocfg = make_output_config(config);

    try
    {
        if(config.value<bool>("recursive"))
            output(make_flat(root),ocfg);
        else
            output(h5::nxgroup(root),ocfg);

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

