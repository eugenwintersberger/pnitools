//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Oct 8,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <iostream>

using namespace pni::core;

//!
//! \brief type determines the detector layout
//! 
//! Currently we support three different types of detectors
//! \li POINT which denotes a point detector
//! \li LINEAR which are 1D strip detectors
//! \li AREA for 2D detectors
//!
//! 
//! 
enum class detector_layout {
    POINT,
    LINEAR,
    AREA};

//----------------------------------------------------------------------------
//!
//! \brief convert string to layout
//!
//! \throws value_error if string value not supported 
//! \param s input string
//! \return detector layout value
//! 
detector_layout layout_from_string(const string &s);

//----------------------------------------------------------------------------
//!
//! \brief convert layout to string 
//! 
//! Converts a detector_layout value to its string representation.
//!
//! \throws value_error if layout has no string representation
//! \param layout the layout value to convert to string
//! \return string representation of the layout
//! 
string string_from_layout(const detector_layout &layout);

//----------------------------------------------------------------------------
//!
//! \brief layout output stream
//!
//! Write the string representation of a detector layout to a stream. If the 
//! layout has no string representation a value_error exception is thrown.
//!
//! \throws value_error if layout has no string representation
//! \param stream the stream to which to write
//! \param l the layout to write
//! \return reference to the modified stream
//!
std::ostream &operator<<(std::ostream &stream,const detector_layout &l);

//----------------------------------------------------------------------------
//!
//! \brief layout from stream
//!
//! Reads the string representation of a layout from a stream. 
//! 
//! \throws value_error if the stream does not provide a layout
//! \param stream the stream to read from
//! \param l reference where to store the layout
//! \return reference to the modified input stream
//!
std::istream &operator>>(std::istream &stream,detector_layout &l);

