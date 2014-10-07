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
// Created on: Oct 7,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "types.hpp"
#include "detector_info.hpp"

enum class file_type { CBF,TIFF,NEXUS};

//!
//! \brief get file type
//! 
//! Determines the type of the file requested by the user. Currently the 
//! following file types are supported 
//! \li CBF (DECTRIS flavor)
//! \li TIFF 
//! \li Nexus (with HDF5 storage backend)
//!
//! An exception is thrown if the file type cannot be determined. The file type 
//! is actually determined by the extension. 
//! 
//! \throws file_error in case of an unkown file type
//! \param f file for which the type should be determined 
//! \return file type enum
//!
file_type get_file_type(const file &f);

//----------------------------------------------------------------------------
//!
//! \brief get detector information
//! 
//! \throws file_error if the file type is unkown
//! 
detector_info_list get_info(const file &f);


