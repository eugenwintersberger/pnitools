//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 12, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include "types.hpp"


//!
//! \brief base class for image operations
//! 
//! Provides the basic interface for image operations. We have to distinguish
//! between two kind operations
//! 
//! \li altering operations 
//! \li non-altering operations
//! 
//! The former ones alter the input image while the latter ones do not. 
//! Virtually all accumulative operations belong to the latter class of 
//! operations.  Image operations like darkfield subtraction and flatfield 
//! correction belong to the former ones. Thus scalar operations are 
//! typically the last ones after a chain of 
//!
class image_op_base
{
    private:
        image_type _result;
    public:
        image_op_base(const image_type &r):_result(r) {}

        //!
        //! \brief perform operation on an image 
        //!
        //! Performs the operation on the. We do not alter the original image 
        //! but rather store the result.
        //!
        virtual void execute(const image_type &image) = 0;

        //---------------------------------------------------------------------
        //!
        //! \brief result shape
        //!
        //! Return the shape of the result stored in a container of type CTYPE. 
        //!  
        //! \tparam CTYPE container type for the shape
        //! \return instance of CTYPE with shape information
        //!
        template<typename CTYPE> CTYPE shape() const 
        {
            return _result.template shape<CTYPE>();
        }

        //---------------------------------------------------------------------
        //!
        //! \brief result size
        //!
        //! Return the number of elements stored in the result. 
        //! \return number of result elements
        //!
        size_t size() const { return _result.size(); }

        //---------------------------------------------------------------------
        //!
        //! \brief result number of dimensions
        //!
        //! Return the number of dimensions of the result.
        //! \return number of result dimensions
        //!
        size_t rank() const { return _result.rank(); }

        //---------------------------------------------------------------------
        //!
        //! \brief get result 
        //! 
        //! Get a constant reference to the result of the operation. 
        //!
        const image_type &result() const { return _result; }

        image_type &result() { return _result; }

        //---------------------------------------------------------------------
        //!
        //! \brief set result 
        //! 
        //! Set the result. This can be used to set an initial value for the 
        //! result. 
        //!
        void result(const image_type &image) { _result = image_type(image); }
};

std::ostream &operator<<(std::ostream &stream,const image_op_base &op);







