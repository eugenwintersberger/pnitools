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

#include "nx_object_path.hpp"

//-----------------------------------------------------------------------------
nx_object_path::nx_object_path(): _elements(), _filename(""), _attrname("") {}

//-----------------------------------------------------------------------------
nx_path_object nx_object_path::from_string(const string &s)
{
    nx_path_object path;

    //check for a filename


    //check for an attribute name 

    //parse the residual string for path elements
    
    return path;
}

//-----------------------------------------------------------------------------
nx_object_path::nx_object_path(const string &path):
    _fname(""),
    _opath(""),
    _attrname("")
{
    //extract the filename (if present)
    size_t file_sep_pos = path.find_first_of(':');
    size_t attr_sep_pos = path.find_first_of('@');

    if(file_sep_pos != path.npos)
    {
        //if the path has a file portion we need to extract not the filename
        _fname = string(path,0,file_sep_pos);
    }

    if(attr_sep_pos != path.npos)
    {
        //extract the attribute name
        _attrname = string(path,attr_sep_pos+1,path.size()-attr_sep_pos);
    }

    //finally wee need to extract the object path
    size_t pstart = ((file_sep_pos == path.npos) ? 0 : file_sep_pos+1);
    size_t pstop = ((attr_sep_pos == path.npos) ? path.size() : attr_sep_pos);
    _opath = string(path,pstart,pstop - pstart);

    //now we have to fix the situation where the string passed is not a 
    //group path but a filename
    if(_opath.find_first_of('.')!=_opath.npos)
    {
        _fname = _opath;
        _opath = "";
    }

}



//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const nx_object_path &path)
{
    o<<path.filename()<<":"<<path.object_path();
    if(path.attribute_name() != "")
        o<<"@"<<path.attribute_name();

    return o;
}

//------------------------------------------------------------------------------
std::istream &operator>>(std::istream &i,nx_object_path &path)
{
    string pstring;
    i>>pstring;
    path = nx_object_path(pstring);
    return i;
}
