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
#include "functor.hpp"

typedef std::vector<functor::pointer_type> functor_vector;

//!
//! \ingroup datgen_devel
//! \brief executes functor stack
//!
//! Executes a stack of functors provided during construction for a 
//! particular point along the x-grid. 
//!
class executor
{
    private:
        //! vector with functors
        functor_vector _functors;
    public:
        //!
        //! \brief constructors
        //!
        //! Creates a new instance of the executor class and moves 
        //! in all functors.
        //! \param functors vector of functors
        //!
        executor(functor_vector &&functors);

        //!
        //! \brief exectute functors
        //!
        //! Execute functors at a given point x along the x-grid and
        //! sum up all the results.
        //! 
        //! \param x point along the x-grid
        //! 
        //! \return sum of all results
        //!
        pni::core::float64 operator()(pni::core::float64 x) const;
};
