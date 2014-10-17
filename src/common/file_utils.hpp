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
// Created on: Jun 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <pni/io/image_info.hpp>

#include "file.hpp"
#include "string_utils.hpp"

//!
//! \ingroup common_devel
//! \brief file type enumeration
//!
//! This enumeration provides a value for each file type supported 
//! by the pnitools program suite. 
//!
enum class file_type { CBF,    //!< denotes DECTRIS CBF files
                       TIF,    //!< TIF files
                       NEXUS,  //!< Nexus/HDF5 files
                       FIO,    //!< DESY FIO files
                       SPEC,   //!< SPEC files
                       SPE     //!< SPE files
                      };

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief get file type
//! 
//! This funciton returns the type of a file. Currently the file type is 
//! determined only by the extension of the file. However, future 
//! implementations may also make use of magic numbers or other mechanisms. 
//!
//! \param input_file the file to determine the type for
//! return instance of file_type
//!
file_type get_file_type(const file &input_file);

//----------------------------------------------------------------------------
//!
//! \ingroup common_devel 
//! \brief checks file extension
//! 
//! Checks if a file has an extension listed in a container of strings. The 
//! template function returns true if the file has one of the extensions in 
//! the container.  Otherwise it returns false.
/*! 
\code{cpp}
file f = ....;
std::vector<string> exts = {".tif",".cbf",".jpg"};

if(has_extension(f,exts))
{
    //do something with the file
}
else
{
    throw file_error(...);
}
\endcode
*/
//! 
//! \tparam CTYPE container type for extensions
//! \param f file to check
//! \param exts instance of CTYPE with extensions
//! \return true
//!
template<typename CTYPE> bool has_extension(const file &f,const CTYPE &exts)
{
    string file_extension = to_lower(f.extension());
    to_lower(file_extension);

    return std::any_of(exts.begin(),exts.end(),
                       [&](const string &s)
                       { return to_lower(s) == to_lower(file_extension);});
}

//-----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief get image information
//! 
//! Returns the image information from a reader type. 
//! \tparam RTYPE reader type
//! \param r reader instance of type RTYPE
//! \param image_nr index of the image in the file 
//!
template<typename RTYPE> 
pni::io::image_info get_image_info(const RTYPE &r,size_t image_nr=0)
{
    return r.info(image_nr);
}
