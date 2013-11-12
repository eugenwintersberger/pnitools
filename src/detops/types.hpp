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

/*!
This header files contains global type definitions for the detops program
*/

#include <pni/core/types.hpp>
#include <pni/core/slice.hpp>
#include <pni/core/arrays.hpp>
#include <vector>

using namespace pni::core;

/*!
\brief ROI type 

A ROI for an image is defined by a pair of two slices, one for each image
dimension. 
*/
typedef std::pair<slice,slice> roi_type;

/*!
\brief ROI stack

If the user passes multiple ROIs to the program they will be stored in a vector.
*/
typedef std::vector<roi_type> roi_stack;

/*!
\brief image type

Though image data of x-ray detectors is usually stored as an integer type, all
operations expect a floating point array as an input. This should ensure that no
problems with roundoff errors occur during numerical calculations.
*/
typedef darray<float64> image_type;

/*!
\brief image stack 

In the case of a user providing several ROIs to the program the requested
operation is applied to each individual ROIs. To get proper performance the
input image is dismantled into smaller images (each representing one ROI) which
are stored in an image stack which is a vector of images.
*/
typedef std::vector<image_type> image_stack;

