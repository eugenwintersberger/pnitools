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
 * Created on: Dec 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "exceptions.hpp"
#include "file.hpp"

//-----------------------------------------------------------------------------
file::file(const string &path):
    _path(path)
{
    if(!fs::is_regular_file(_path) || 
       fs::is_directory(_path) ||
       !fs::exists(_path))
    {
        throw file_error(EXCEPTION_RECORD,"File ["+path+"] is not a regular"
                        "file!");
    }
}

//-----------------------------------------------------------------------------
string file::name() const
{
    return string(_path.filename());
}

//-----------------------------------------------------------------------------
string file::base() const
{
    return _path.parent_path().string(); 
}

//-----------------------------------------------------------------------------
string file::extension() const
{
    return string(_path.extension());
}

//-----------------------------------------------------------------------------
string file::path() const
{
    return _path.string();
}
