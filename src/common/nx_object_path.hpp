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

#include <pni/core/types.hpp>
#include <utility>

using namespace pni::core;

typedef std:pair<string,string> path_element;

/*!
\brief representing path to an Nexus object

This class represents the path of an object within a Nexus file. 
A user can specify a Nexus object by a string using the following
syntax
\code
[<Filename>://]<path to object>[@attribute name]
\endcode
The path to the object itself consist of elements of form 
\code
name:class
\endcode
where the first part is the name of the object and the second one the class.
An element can consist either of a single class or name or both. 
Here are some examples of valid Nexus paths

Lets start with the most simplest case - a path containing only object names
\code
/entry/sample/polar_angle
\endcode
one can become more specific by adding the classes
\code
/entry:NXentry/sample:NXsample/polar_angle
\endcode
If there is only one entry in the file and usually only one sample below an
entry the above path can be simplified with
\code
/:NXentry/:NXsample/polar_angle
\endcode
The paths shown until now are all absolute. In some applications one may wants
to use a relative path. For instance let's assume that the current group is the
entry group. In this case the above path would reduce to 
\code
:NXsample/polar_angle
\endcode
Command line programs might want to use this class to specify the full path of
an object including the file as an argument. In such a case one can prefix the
path to the file 
\code
./path/to/nexus_file.h5://:NXentry/:NXsample/rotation_angle
\endcode
In all the above examples a field has been addressed by the path. Obviously the
same holds for groups. If we would like to obtain the group that holds sample
related fields we can modify the above path to
\code
./path/to/nexus_file.h5://:NXentry/:NXsample
\endcode
The nx_object_path address attributes too. In such a case just append a
@<attribute_name> to the path
\code
./path/to/nexus_file.h5://:NXentry/:NXsample@creation_time
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
        //! seperator of object name and class
        static const char class_seperator = ':';
        //! seperator for path elements
        static const char element_seperator = '/';
        //! attribute separator
        static const char attribute_sepeartor = '@';

        //!path elements
        std::list<path_element> _elements;

        //! name of the file where the object is stored
        string _filename;
        //! name of the attribute
        string _attrname;

        //---------------------------------------------------------------------
        /*!
        \brief set filename 

        Set the filname of the path object.
        \param s name of the file
        */
        void filename(const string &s) { _filename = s; }

        //---------------------------------------------------------------------
        /*!
        \brief set attribute name
         
        Set the attribute name of the path.
        \param s name of the attribute
        */
        void attrname(const string &s) { _attrname = s; } 
    public:
        //=====================public member types=============================
        //! read write iterator
        typedef std::list<path_element>::iterator iterator;

        //! const iterator
        typedef std::list<path_element>::const_iterator const_iterator;
        //====================constructor and destructor=======================
        //! default constructor
        explicit nx_object_path();

        //---------------------------------------------------------------------
        //! destructor
        ~nx_object_path() {}

        //---------------------------------------------------------------------
        //! get file name
        string filename() const { return _fname; }

        //---------------------------------------------------------------------
        //! get attribute name
        string attribute_name() const { return _attrname; }

        //--------------------------------------------------------------------
        /*!
        \brief get iterator to first path element

        Returns a non-constant iterator to the first element of the path. 
        \return iterator
        */
        iterator begin() { return _elements.begin(); }

        //---------------------------------------------------------------------
        /*!
        \brief get iterator to the last+1 element

        Returns a non-constant iterator to the last+1 path element.
        \return iterator
        */
        iterator end() { return _elements.end(); }

        //---------------------------------------------------------------------
        /*!
        \brief get a const. iterator

        Returns a const iterator to the first path element.
        \return const iterator
        */
        const_iterator begin() const { return _elements.begin(); }

        //---------------------------------------------------------------------
        /*!
        \brief get a const. iterator 

        Returns a const iterator to the last+1 element of the path.
        \return const iterator
        */
        const_iterator end() const { return _elements.end(); } 

        //---------------------------------------------------------------------
        /*!
        \brief append path element

        Appends a path element. 
        \param e path element 
        */
        void push_pack(const path_element e)
        {
            _elements.push_back(e);
        }

        //---------------------------------------------------------------------

        //!--------------------------------------------------------------------
        /*! 
        \brief path is absolute

        Method returns true if the path is an absolute path starting from the
        root of the file. Otherwise the path is considered as relative meaning
        relative to the actual position in a Nexus tree.
        \return true if path is absolute
        */
        bool is_absolute() const;

        //=================some static methods to create a path================
        /*!
        \brief factory function

        This static factory function creates a path object from a string.
        \param s string holding the path
        */
        static nx_object_path from_string(const string &s);
};

//! output operator for NXObjectPath
std::ostream &operator<<(std::ostream &o,const nx_object_path &path);

//! input operator for NXObjectPath
std::istream &operator>>(std::istream &i,nx_object_path &path);


