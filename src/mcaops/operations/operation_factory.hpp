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

#include <pni/core/configuration.hpp>
#include "operation.hpp"

//!
//! \ingroup mcaops_ops_devel
//! \brief factory creating different operations
//! 
//! This class provides a single static method 'create' which is used to 
//! create an instance of a particular operator. 
//!
class operation_factory
{
    public:

        //!
        //! \brief create operation instance
        //! 
        //! Return an instance of the requested operation. The operation is 
        //! identified by its name which is passed as the only argument 
        //! to this function. If no operation for a given name is found a 
        //! key_error exception is thrown.
        //!
        //! \throws key_error if no operation of the given name exists
        //! \param name operation name
        //! \return smart pointer to the operation 
        //! 
        static operation::pointer_type create(const pni::core::string &name);
};



