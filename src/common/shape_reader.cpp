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
 * Created on: Dec 18, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "shape_reader.hpp"

//-----------------------------------------------------------------------------
shape_reader::shape_reader()
{
    e = boost::regex("\\d+");
}

//-----------------------------------------------------------------------------
shape_reader::shape_reader(char st,char et,String s)
{
    e = boost::regex("\\d+");
}

//-----------------------------------------------------------------------------
shape_t shape_reader::read(const String &s) 
{
    std::cout<<s<<std::endl;
    boost::match_results<String::const_iterator> what;
    boost::regex_match(s,what,e);

    std::cout<<what.size()<<std::endl;
    for(auto match: what)
        std::cout<<match<<std::endl;

    return shape_t();

}
