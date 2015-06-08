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
// Created on: 8 May, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
 
#include <pni/core/types.hpp>

//!
//! \ingroup datgen_devel
//! \brief grid generator
//! 
//! A simple generator for a regular grid. 
class grid_generator
{
    private:
        //! the current value of the generator
        pni::core::float64 _value;
        //! the step width 
        pni::core::float64 _delta;
    public:
        //--------------------------------------------------------------------
        //! default constructor
        grid_generator();

        //--------------------------------------------------------------------
        //! 
        //! \brief constructor
        //! 
        //! \param start the first grid value
        //! \param delta the step size along the grid
        //! 
        grid_generator(pni::core::float64 start,pni::core::float64 delta);

        //! 
        //! \brief reset start value
        //! 
        //! Resets the start value for the generator. 
        //! 
        //! \param start the new start value for the generator
        //!
        void start(pni::core::float64 start);

        //--------------------------------------------------------------------
        //!
        //! \brief set the step width
        //! 
        //! This method resets the step width used for the grid generator
        //! 
        //! \param delta the step width along the grid
        //!
        void delta(pni::core::float64 delta); 

        //--------------------------------------------------------------------
        //! 
        //! \brief return next grid value
        //!
        //! Returns the next value along the grid.
        //! \return next grid value
        //!
        pni::core::float64 operator()();
};


