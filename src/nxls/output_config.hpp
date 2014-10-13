//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <cstdlib>

//!
//! \brief output configuration
//! 
//! Output configuration for nxls. This assembled from the configuation 
//! provided by the user via the command line. 
//! 
class output_config
{
        //! give long output
        bool _long;
        //! output includes attributes
        bool _with_attributes;
        //! trim level - the number of elements to chop of from the path
        //! of an object
        size_t _trim_level;

    public:
        //! 
        //! \brief constructor
        //! 
        //! \param l long output
        //! \param a output with attributes
        //! \param t trim level
        //! 
        explicit output_config(bool l,bool a,size_t t);

        //--------------------------------------------------------------------
        //! 
        //! \brief get long output flag
        //! 
        //! \return true if long output is set 
        //! 
        bool long_output() const;

        //--------------------------------------------------------------------
        //! 
        //! \brief attribute output
        //!
        //! \return true if attributes should be included 
        //!
        bool with_attributes() const;

        //--------------------------------------------------------------------
        //! 
        //! \brief trim level for path
        //! 
        //! Returns the number of elements to remove from an objects path.
        //! If this value is 0 to trimming will be done.
        //! 
        //! \return number of path elements to remove
        //! 
        size_t trim_level() const;
};
