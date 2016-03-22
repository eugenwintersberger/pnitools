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
#include <pni/core/error.hpp>

#include "average.hpp"

namespace algorithms
{
    //!
    //! \ingroup common_devel
    //! \brief rebin data between two ranges 
	//!
	//! \tparam ITERT1 type of the two input iterators
	//! \tparam ITERT2 type of the output iterator
	//! \param ifirst start iterator of input
	//! \param ilast  end iterator of input
	//! \param ofirst start iterator of the output container
	//! \param bsize  number of bins to average
	//! \param normalize if true the output data will be normalized
    //! 
    template<
             typename ITERT1,
             typename ITERT2
            >
    void rebin(ITERT1 ifirst,ITERT1 ilast,ITERT2 ofirst,size_t bsize,
               bool normalize)
    {
        using namespace pni::core;
        using value_type = typename ITERT1::value_type;
        
        //check size of input range
        if(std::distance(ifirst,ilast)<bsize)
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Input range is smaller than block size!");

        //initialize the moving iterator
        ITERT1 imove = ifirst;
        std::advance(imove,bsize);

        //mail loop
        while(imove != ilast)
        {
            if(normalize)
                *ofirst++ = average(ifirst,imove);
            else
                *ofirst++ = sum(ifirst,imove);

            //advance the input iterators
            std::advance(ifirst,bsize);
            if(std::distance(imove,ilast)<=bsize)
                imove = ilast;
            else
                std::advance(imove,bsize);

        }

        if(normalize)
            *ofirst++ = average(ifirst,imove);
        else
            *ofirst++ = sum(ifirst,imove);
    }

//end of namespace
}
