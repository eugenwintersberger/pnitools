//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: 03.06.2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#pragma once

#include <pni/core/types.hpp>

#include "operation.hpp"

using namespace pni::core;

//!
//! \ingroup mcaops_devel
//! \brief compute summ of input data
//! 
//! Compute the sum of the input data and output the result.
//!
class sum_operation:public operation
{
    private:
        //!sum
        float64 _sum;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        sum_operation():
            operation(),
            _sum(0)
        {}

        //---------------------------------------------------------------------
        //! destructor
        ~sum_operation(){}

        //---------------------------------------------------------------------
        //! execute operation
        virtual void operator()(const array_type &channels,
                                const array_type &data)
        {
            if(this->verbose())
                std::cout<<"Execute sum operation ..."<<std::endl;

            _sum = 0;
            _sum = std::accumulate(data.begin(),data.end(),float64(0));
        }


        //---------------------------------------------------------------------
        //! write result to output stream
        virtual std::ostream &stream_result(std::ostream &o) const
        {
            o<<_sum;
            return o;
        }
};

