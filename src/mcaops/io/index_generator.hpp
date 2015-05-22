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
// Created on: May 22, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>

//!
//! \ingroup mcaops_devel
//! \brief channel index generator
//!
//! This is a functor which generates a channel index. A call to operator()
//! returns the current index and increments the internal index value. 
//!
class index_generator
{
    private:
        size_t _index; //!< offset from which to start
    public:
        //! 
        //! \brief constructor
        //! 
        //! The default constructor setting the offset to 0.
        //!
        index_generator();
        
        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Constructor which allows a custom offset. 
        //!
        //! \param offset the starting value of the index generator
        //!
        index_generator(size_t offset);

        //--------------------------------------------------------------------
        //!
        //! \brief get index and increment
        //!
        //! Returns the current index and increments the internal index value.
        //!
        //! \return current channel index
        //!
        size_t operator()();
        
        //--------------------------------------------------------------------
        //!
        //! \brief get current index
        //!
        //! Unlike the operator() this member function just returns the 
        //! current channel index but does not increment the internal 
        //! index.
        //!
        //! \return current channel index
        //!
        size_t index() const;
};
