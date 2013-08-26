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

#include "environment.hpp"

//-----------------------------------------------------------------------------
environment::environment(nxfile file):
    _file(file),
    _current_group(file["/"])
{ }

//-----------------------------------------------------------------------------
environment::environment(nxfile file,const string &path):
    _file(file),
    _current_group(file[path])
{ }

//-----------------------------------------------------------------------------
environment::~environment()
{
    _current_group.close();
    _file.close();
}

//-----------------------------------------------------------------------------
string environment::get_current_path() const
{
    return _file.name()+":"+_current_group.path();
}

//-----------------------------------------------------------------------------
void environment::current_group(const string &path)
{
    //go one level up
    if(path == "..")
    {
        _current_group = _current_group.parent();
        return;
    }

    //need to check if the target is a group
    nxobject o = _current_group[path];
    if(o.object_type() == pni::io::nx::nxobject_type::NXFIELD)
        std::cout<<"You cannot cd to a field!"<<std::endl;
    else
        _current_group = nxgroup(o);
}

