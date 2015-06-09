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

#include <random>
#include "functor.hpp"

//!
//! \ingroup datgen_devel
//! \brief implementation of a random number generator
//! 
//! Computes uniformely distributed random numbers in a particular interval. 
//!
class uniform : public functor
{
    private:
        typedef std::uniform_real_distribution<pni::core::float64>
            distribution_type;

        mutable std::mt19937      _generator;
        mutable distribution_type _distribution;

    public:
        //! constructor
        uniform(pni::core::float64 lower_bound,pni::core::float64 upper_bound);

        //! execute operation
        virtual pni::core::float64 operator()(pni::core::float64 x) const;

        //! write parameters to stream
        virtual std::ostream &to_stream(std::ostream &stream) const;
};
