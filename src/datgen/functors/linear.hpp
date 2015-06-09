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

#include "functor.hpp"

//!
//! \ingroup datgen_devel
//! \brief implementation of a linear functor
//! 
//! This functor computes a linear function. 
//!
class linear : public functor
{
    private:
        //! slope of the linear function
        pni::core::float64 _slope;
        //! offset of the linear function
        pni::core::float64 _offset;
    public:
        //! 
        //! \brief constructor
        //! 
        //! \param slope the slope of the function
        //! \param offset the offset of the function
        linear(pni::core::float64 slope,pni::core::float64 offset);

        //! compute result
        virtual pni::core::float64 operator()(pni::core::float64 x) const;

        //! output to stream
        virtual std::ostream &to_stream(std::ostream &stream) const;
    
};
