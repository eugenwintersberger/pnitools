//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 9, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <map>
#include <pni/core/types.hpp>


//!
//! \ingroup datgen_devel
//! \brief type to store command line arguments
//!
typedef std::vector<pni::core::string> args_vector;

//!
//! \ingroup datgen_devel
//! \brief map for argumen vectors
//!
typedef std::multimap<pni::core::string,args_vector> args_map;


//!
//! \ingroup datgen_devel 
//! \brief split input arguments
//! 
//! This class splits a vector with input arguments and options at positions
//! denoted by a list of keywords. These keywords mark the beginning of a 
//! new options stream. The splitter can be used to group command line 
//! options according to the keywords.
//!
class options_splitter
{
    private:
        //! internal list of keywords
        args_vector _keywords;
    public:
        //! constructor
        options_splitter(const args_vector &kewords);

        //!
        //! \brief splits argument vector
        //!
        //! Splits the argument vector args provided by the user according 
        //! to the list of keywords provided to the class during 
        //! construction.
        //! 
        //! If an empty keyword list has been passed to during construction
        //! the input vector will be passed through unchanged.
        //!
        //! 
        args_map operator()(const args_vector &args);
};
