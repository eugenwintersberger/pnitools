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
///

#pragma once

#include <pni/core/configuration.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/parsers/slice_parser.hpp>
#include "types.hpp"


using namespace pni::io;

//!
//! \brief get ROI from a string 
//! 
//! Construct a ROI from a string passed by the use with the -r option. 
//! 
//! \throws parser_error in case of errors
//! \param s input string which should be parsed
//! \return instance of roi_type
//!
roi_type get_roi_from_string(const string &s);

//-----------------------------------------------------------------------------
//!
//! \brief get roi stack from configuration
//! 
//! Construct a stack of ROIs from the program configuration.  If now ROIs 
//! are passed by the user an empty stack is returned.
//! 
//! \throws parser_error in case of errors
//! \param config current program configuration
//! \return stack of rois
//!
roi_stack get_roi_stack(const configuration &config);

//------------------------------------------------------------------------------
//!
//! \brief select roi from image
//! 
//! Template function selecting a roi from an image and storing its data to a 
//! new image. 
//! 
//! \tparam ITYPE input image type
//! \param image instance of ITYPE with image of original size
//! \param roi the ROI to select from the image
//! \return instance of image_type with the ROI data
//!
template<typename ITYPE>
image_type get_roi( ITYPE &image,const roi_type &roi)
{
    return image_type(image(roi.first,roi.second));
}

//-----------------------------------------------------------------------------
//!
//! \brief creates an image stack from a roi stack
//! 
//! This function template creates a image stack from a single image and a roi
//! stack. 
//! 
//! \tparam ITYPE image type
//!
template<typename ITYPE>
image_stack image_stack_from_rois(ITYPE &image,const roi_stack &rois)
{
    image_stack istack;

    for(auto roi: rois) istack.push_back(get_roi(image,roi));

    return istack;
}
