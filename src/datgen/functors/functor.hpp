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

#include <memory>
#include <iostream>
#include <pni/core/types.hpp>

//!
//! \ingroup datgen_devel
//! \brief abstract functor type
//! 
//! This class defines the basic interface for all functors used in datgen. 
//! 
class functor
{
    public:
        //! shared pointer type to a functor
        typedef std::unique_ptr<functor> pointer_type;

        //! virtual distructor for polymorphy
        virtual ~functor();

        //--------------------------------------------------------------------
        //! 
        //! \brief execute function
        //! 
        //! Abstract virtual method performing the actual computation. 
        //! 
        //! \param x input argument
        //! \return result of the computation
        virtual pni::core::float64 operator()(pni::core::float64 x) const = 0;

        //--------------------------------------------------------------------
        //! 
        //! \brief write params to stream
        //! 
        //! Write functor parameters to an output stream. 
        //! This function is mainly for debugging purposes. 
        //! 
        //! \param stream the output stream
        //! \return modified output stream
        //! 
        virtual std::ostream &to_stream(std::ostream &stream) const = 0;
};

//! 
//! \ingroup datgen_devel
//! \brief output operator for functors
//! 
//! Write a functor to an output stream. 
std::ostream &operator<<(std::ostream &stream,const functor &f);
