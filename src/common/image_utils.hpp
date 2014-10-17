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
// Created on: Oct 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/image_info.hpp>
#include <pni/io/image_reader.hpp>

class file;

using namespace pni::core;
using namespace pni::io;

//! a unique pointer to a image reader
typedef std::unique_ptr<pni::io::image_reader> image_reader_ptr;

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief get image reader
//!
//! Return a pointer to an image reader. 
//!
//! \throws file_type_error if the input file type is not supported
//! \param image_file the image file
//! \return pointer to reader
//!
image_reader_ptr get_image_reader(const file &image_file);

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief get image information
//!
//! Return image information for an image stored in a file.
//!
//! \throw file_type_error if the file type is unknown
//! \param image_file the input file
//! \return instance of image_info
//!
image_info get_image_info(const file &image_file);



