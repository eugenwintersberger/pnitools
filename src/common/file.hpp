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

#pragma once

#include <pni/core/types.hpp>
#include <boost/filesystem.hpp>

using namespace pni::core;
namespace fs = boost::filesystem;

/*!
\ingroup common_code
\brief class describing a single file

This class represents a single file stored somewhere on the file system. Its
only purpose is to give easy access to all the parameters of the file.
*/
class file
{
    private:
        //! boost path object representing the file
        fs::path _path;
    public:
        //========================constructors and destructor==================
        //! default constructor
        file():_path() {}

        //---------------------------------------------------------------------
        /*!
        \brief constructor

        Constructor taking a string representing the full path to the file.
        \param f path to the file
        */
        file(const string &path);

        //---------------------------------------------------------------------
        //! destructor
        ~file() {}

        //=================general purpose methods=============================
        //! return the name of the file
        string name() const;

        //---------------------------------------------------------------------
        //! return the path to the file
        string base() const;

        //---------------------------------------------------------------------
        //! return the extension of the file
        string extension() const;

        //---------------------------------------------------------------------
        //! true if this is a regular file
        bool is_file() const;

        //---------------------------------------------------------------------
        //! return the full path of the file
        string path() const;
};
