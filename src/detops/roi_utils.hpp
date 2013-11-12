/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Nov 12, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include "types.hpp"

//------------------------------------------------------------------------------
/*!
\brief select roi from image

Template function selecting a roi from an image and storing its data to a new
image. 

\tparam ITYPE input image type
\param image instance of ITYPE with image of original size
\param roi the ROI to select from the image
\return instance of image_type with the ROI data
*/
template<typename ITYPE>
image_type get_roi(const ITYPE &image,const roi_type &roi)
{
    return image_type(image(roi.first,roi.second));
}

//-----------------------------------------------------------------------------
/*!
\brief creates an image stack from a roi stack

This function template creates a image stack from a single image and a roi
stack. 

\tparam ITYPE image type
*/
template<typename ITYPE>
image_stack image_stack_from_rois(const ITYPE &image,const roi_stack &rois)
{
    image_stack istack;
    for(auto roi: rois)
        istack.push_back(get_roi(image,roi));

    return istack;
}
