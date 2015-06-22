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

#include <iostream>
#include <pni/core/arrays/slice.hpp>
#include <pni/io/parsers.hpp>
#include <vector>

//!
//! \ingroup common_devel
//! 
//! Region of interest. This is a vector of slices. With this we can handle
//! ROIs of an arbitrary number of dimensions. We can thus use this 
//! in mcaops and in imgops. By using the slice object we can even define 
//! ROIs with strides not equal to one. 
typedef std::vector<pni::core::slice> roi_type; 

//----------------------------------------------------------------------------
//! 
//! \ingroup common_devel 
//! \brief number of elements in the ROI
//!
//! This function computes the number of elements in a region of interest. 
//! If the stri
size_t size(const roi_type &roi);

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief return number of dimensions
//!
//! Return the number of dimensions of a ROI. This might be useful in 
//! cases where the ROI has to be of a certain dimension. This is 
//! basically the number of elements in the vector from which the 
//! ROI is assembled. 
//! 
//! \param roi reference to the particular region of interest
//! \return number of dimension
//!
size_t rank(const roi_type &roi);

//---------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief input operator for a ROI
//! 
//! This operator is required to make rois available from the command line. 
//! 
std::istream &operator>>(std::istream &stream,roi_type &roi);


template<typename ITERT1>
void apply_roi_to_iterators(roi_type::const_iterator &r,ITERT1 &first,ITERT1 &last)
{
    size_t s = std::distance(first,last);
    std::advance(first,r->first()-1);
    std::advance(last,-(s-r->last()+1));
}

template<typename ITERT1,typename ...ITERT>
void apply_roi_to_iterators(roi_type::const_iterator &r,ITERT1 &first,ITERT1 &last,ITERT& ...iterators)
{
    apply_roi_to_iterators(r,first,last);

    r++;
    apply_roi_to_iterators(r,iterators...);
}

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! 
//! Apply a ROI to a bunch of iterators. 
//!
template<typename ...ITERT>
void apply_roi_to_iterators(const roi_type &roi,ITERT& ...iterators)
{
    auto riter = roi.begin();
    apply_roi_to_iterators(riter,iterators...);
}
