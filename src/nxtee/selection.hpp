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
//************************************************************************
// Created on: Jun 3, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <pni/core/arrays/slice.hpp>

//!
//! \ingroup nxtee_devel 
//! \brief selection_type 
//! 
//! A type used to store selections. 
//! 
struct selection
{
    typedef std::vector<pni::core::slice> type;

    //!
    //! \brief create selection from shape
    //!
    //! Creates a selection from a shape which whouls span the entire
    //! multidimensional data described by the particular shape.
    //!
    //! \tparam CTYPE container type used to store shape information
    //! \param shape reference to the actual shape container
    //! \return selection type.
    //!
    template<typename CTYPE>
    static type from_shape(const CTYPE &shape)
    {
        using namespace pni::core;
        type sel;

        for(auto s: shape)
        {
            if(s)
                sel.push_back(slice(0,s));
            else
                sel.push_back(slice(0,1));
        }

        return sel;
    }

};

