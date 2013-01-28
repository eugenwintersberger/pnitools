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

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;


/*!
\brief basic shell environment

This class holds the environment for the Nexus shell. Currently this includes
only the file and the current group. 
*/
class environment
{
    private:
        nxfile _file; //!< currently opened file
        nxgroup _current_group; //!< current group
    public:
        //=====================constructor and destructor=======================
        //! default constructor
        environment() {}
        //----------------------------------------------------------------------
        /*! 
        \brief constructor

        Constructor taking only the file as an argument. The current group is in
        this case the root group /.
        \param file Nexus file to work on
        */
        environment(nxfile file);

        //---------------------------------------------------------------------
        /*! 
        \brief constructor

        Constructor with file and path to the new working group. 
        \param file file to work on 
        \param path the path to the new working group
        */
        environment(nxfile file,const string &path);

        //---------------------------------------------------------------------
        //! destructor
        ~environment();

        //======================public member functions========================
        //! get file reference
        const nxfile &file() const { return _file; }

        //---------------------------------------------------------------------
        //! get group reference
        const nxgroup &current_group() const { return _current_group; }

        //!--------------------------------------------------------------------
        //! set the current group
        void current_group(const string &path);

        //---------------------------------------------------------------------
        //! get curent path 
        string get_current_path() const;

};
