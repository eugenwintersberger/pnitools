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

#include "xml_utils.hpp"

//-----------------------------------------------------------------------------
shape_t dimensions2shape(const tree::ptree &dims)
{
    size_t rank = dims.get<size_t>("<xmlattr>.rank");
    shape_t s(rank);

    //initialize the shape with zero
    std::fill(s.begin(),s.end(),0);

#ifdef NOFOREACH
    BOOST_FOREACH(auto dim,dims)
#else
    for(auto dim: dims)
#endif
    {
        if(dim.first != "dim") continue;

        auto index = dim.second.get<size_t>("<xmlattr>.index");
        auto value = dim.second.get<size_t>("<xmlattr>.value");
        s[index-1] = value;
    }

    return s;
}

//-----------------------------------------------------------------------------
bool open_xml_file(const string &fname,tree::ptree &tree)
{
    try
    {
        tree::read_xml(fname,tree);
    }
    catch(...)
    {
        std::cerr<<"Error reading XML file "<<fname<<"!"<<std::endl;
        return true;
    }

    return false;
}
