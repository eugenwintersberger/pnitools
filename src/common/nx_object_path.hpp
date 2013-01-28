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

#pragma once

#include<pni/core/types.hpp>

using namespace pni::core;

/*!
\brief representing path to an Nexus object

This class represents the path of an object within a Nexus file. 
A user can specify a Nexus object from the command line using the following
syntax
\code
<Filename>:<path to object>[@attribute name]
\endcode
Using this one can not only address a group or a field but also a particular
attribute.
The class provides access to the different components of such a path:
\li the file name
\li the path to the object with the file
\li and the optional attribute name

If the attribute name is an empty string the path refers to a group or field
object. If the path should only represent an internal path one can omit the file
name part.
*/
class nx_object_path
{
    private:
        //! name of the file where the object is stored
        string _fname;
        //! path to the object
        string _opath;
        //! name of the attribute
        string _attrname;
    public:
        //====================constructor and destructor=======================
        //! default constructor
        explicit nx_object_path();

        //---------------------------------------------------------------------
        //! constructor
        explicit nx_object_path(const string &p);

        //---------------------------------------------------------------------
        //! constructor
        explicit nx_object_path(const string &f,const string &p,const string &a);

        //---------------------------------------------------------------------
        //! destructor
        ~nx_object_path() {}

        //---------------------------------------------------------------------
        //! get file name
        string filename() const { return _fname; }

        //---------------------------------------------------------------------
        //! get object path
        string object_path() const { return _opath; }

        //---------------------------------------------------------------------
        //! get attribute name
        string attribute_name() const { return _attrname; }
};

//! output operator for NXObjectPath
std::ostream &operator<<(std::ostream &o,const nx_object_path &path);

//! input operator for NXObjectPath
std::istream &operator>>(std::istream &i,nx_object_path &path);

