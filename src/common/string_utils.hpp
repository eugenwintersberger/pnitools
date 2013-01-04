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
 * Created on: Oct 18, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

/*!
\brief trim a string

Remove leading and trailing blanks from a string.
\param s string to trim
\return trimmed string
*/
String trim(const String &s);

//-----------------------------------------------------------------------------
/*!
\brief read shape 

Read a shape from a string and store the result in a container defined by the
user. 
\tparam STYPE STL compliant container type
\param s string from which to construct the shape
\return container with shape data
*/
template<typename STYPE> STYPE read_shape(const String &s)
{
    boost::regex sr("\\d+");
    String::const_iterator start = s.begin();
    String::const_iterator end = s.end();
    boost::smatch match;
    STYPE shape;

    while(boost::regex_search(start,end,match,sr))
    {
        for(auto value: match)
            shape.push_back(boost::lexical_cast<typename STYPE::value_type>(value));

        start = match[0].second;
    }
    return shape;
}

