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
//! \brief implementation of a gauss functor
//! 
//! This functor implements a gauss function.
//! 
class gauss : public functor
{
    private:
        //! sigma value of the gaussian
        pni::core::float64 _sigma;
        //! center value 
        pni::core::float64 _mu;
        //! amplitude
        pni::core::float64 _amp;
    public:
        //! constructor
        gauss(pni::core::float64 sigma,pni::core::float64 mu,
              pni::core::float64 amplitude);

        //! execute function
        virtual pni::core::float64 operator()(pni::core::float64 x) const;

        //! output to stream
        virtual std::ostream &to_stream(std::ostream &stream) const;
};
