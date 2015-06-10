//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/formatters.hpp>

typedef pni::io::formatter<pni::core::float64> float64_fmt_type;
typedef pni::io::formatter<size_t>             size_t_fmt_type;

//!
//! \ingroup mcaops_ops_devel
//! \brief base class for operations
//! 
//! This class provides the basic interface for all operations (commands) that
//! can be performed with mcaops.
//! 
//! An operation takes a pair of data ranges as its input where a data range 
//! is a pair of \a begin \a end iterators. The first range runs over the 
//! channel index/bin-center values and the second over the MCA data. Using 
//! iterators as input arguments makes the application of ROIs simple as we 
//! only have to adjust the two iterators for each range according to a given 
//! ROI. 
//!
//! Only a default constructor is provided. All further configuration of the 
//! operation must be done via its configure() method. In the current
//! implementation a list of command line options is passed to this member 
//! function from which every operation has to extract those options 
//! it requires. 
//!
//! From the point of the main program an operation will be recieved as a 
//! smart pointer which allows for polymorphy. 
//!
class operation
{
    public:
        //=================public types========================================
        //! general array type
        typedef pni::core::dynamic_array<pni::core::float64> array_type;
        //! iterator type
        typedef array_type::const_iterator data_iterator;
        //! argument vector
        typedef std::vector<pni::core::string> args_vector;

        //--------------------------------------------------------------------
        //! 
        //! \brief range over input data
        //! 
        //! The first element of the pair is the start iterator, the second the 
        //! end iterator over the data range the operation has to process. 
        typedef std::pair<data_iterator,data_iterator> data_range;

        //--------------------------------------------------------------------
        //!
        //! \brief argument type for each operation
        //!
        //! The first element of the pair is the channel/bin center range
        //! while the second one is the MCA data range.
        typedef std::pair<data_range,data_range> argument_type;

        //--------------------------------------------------------------------
        //! 
        //! \brief operation pointer type
        //! 
        //! Used only for polymorphy. 
        //! 
        typedef std::unique_ptr<operation> pointer_type;
    
        //---------------------------------------------------------------------
        //! default constructor
        operation();

        //---------------------------------------------------------------------
        //! destructor (has to be virtual)
        virtual ~operation();

        //---------------------------------------------------------------------
        //!
        //! \brief configure operation
        //! 
        //! This method configures the operation according to command line 
        //! options provided by the user. 
        //! 

        virtual args_vector configure(const args_vector &args) = 0;

        //---------------------------------------------------------------------
        //!
        //! \brief execute the operation
        //! 
        //! Abstact method - each operation has to implement this method which 
        //! finally executes the operation requested by the user. 
        //!
        //! \param arg reference to the input argument 
        //!
        virtual void operator()(const argument_type &arg) = 0;

        //---------------------------------------------------------------------
        //!
        //! \brief write output to stream
        //! 
        //! Write the result of the operation. Currently the output is written
        //! to a simple stream. This may changes in future. 
        //! This method must be implemented by every concrete operation and is 
        //! called by the << operator for the operation type.
        //!
        //! \param output stream
        //!
        virtual std::ostream &stream_result(std::ostream &o) const = 0;
};

//-----------------------------------------------------------------------------
//! write operation to output stream
std::ostream &operator<<(std::ostream &o,const operation &op);


