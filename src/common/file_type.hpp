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
// Created on: May 22, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "file.hpp"

//!
//! \ingroup common_devel
//! \brief file types
//!
//! This enumeration describes several file types 
//!
enum class file_type { UNKNOWN,    //!< unknown file type
                       NEXUS_FILE, //!< the file is a Nexus file
                       SPEC_FILE,  //!< the file is a SPEC file
                       FIO_FILE,   //!< the file is a FIO file
                       TIFF_FILE,  //!< a TIFF image file
                       CBF_FILE    //!< a CBF file
                     };

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief return file type
//!
//! Returns the file type for a file determined by its name. The file type is 
//! determined by means of magic bytes. If this is not possible, the files
//! extension is used.
//!
//! \param fname name of the file
//! \return file type enumeration
file_type get_file_type(const pni::core::string &fname);

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief return file type
//!
//! Returns the file type for a file determined by its name. The file type is 
//! determined by means of magic bytes. If this is not possible, the files
//! extension is used.
//!
//! \param f reference to a file object
//! \return file type enumeration
file_type get_file_type(const file &f);
