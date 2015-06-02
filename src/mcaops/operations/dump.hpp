//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 14,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "operation.hpp"

//!
//! \ingroup mcaops_ops_devel
//! \brief pass through 
//! 
//! The dump operation takes the input and passes it through without 
//! modification.  One application would be to read data from standard input 
//! or a file and print it to stdandard out.
//!
class dump:public operation
{
    private:
        argument_type _data;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        dump();

        //---------------------------------------------------------------------
        //! destructor
        ~dump();

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

