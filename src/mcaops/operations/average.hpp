//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Mar 21, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#pragma once

#include <pni/core/arrays/slice.hpp>
#include <pni/core/types.hpp>

#include "operation.hpp"

//!
//! \ingroup mcaops_ops_devel
//! \brief compute average of bin contents
//! 
//! Compute the averager of the input data and output the result.
//!
class average:public operation
{
    private:
        //!sum
        pni::core::float64 _average;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        average();

        //---------------------------------------------------------------------
        //! destructor
        ~average();

        //---------------------------------------------------------------------
        //! configuration
        virtual args_vector configure(const args_vector &args);

        //---------------------------------------------------------------------
        //! execute operation
        virtual void operator()(const argument_type &data);

        //---------------------------------------------------------------------
        //! write result to output stream
        virtual std::ostream &stream_result(std::ostream &o) const;
};

