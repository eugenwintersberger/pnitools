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
// Created on: Jun 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <algorithm>
#include <numeric>
#include <pni/core/error.hpp>

namespace algorithms
{
    //!
    //! \ingroup common_devel
    //! \brief compute sum of range
    //! 
    //! Compute the sum of all elements in the range defined by the two 
    //! iterators \c first and \c last. 
    //!
	//! \tparam ITERT iterator type for the input container
    //! \param first iterator to the first element in the range
    //! \param last iterator to the final element in the range
    //! \return sum of all elements
    //!
    template<typename ITERT>
    typename ITERT::value_type sum(ITERT first,ITERT last)
    {
        typedef typename ITERT::value_type value_type;
        return std::accumulate(first,last,value_type(0));
    }
}
