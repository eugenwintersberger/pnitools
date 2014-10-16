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
// Created on: Oct 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/image_reader.hpp>


//!
//! \ingroup det2nx_devel
//! \brief create reader instances
//!
//! Provides a reader for a particular file format. 
//!

class reader_factory
{
    public:
        //! smart pointer for the reader
        typedef std::unique_ptr<pni::ioimage_reader> pointer_type;

        //! 
        //! \brief generate reader
        //!
        //! Currently the file formats CBF and TIF are supported.
        //!
        //! \param format string with either "CBF" or "TIF"
        //! \return pointer to reader instance
        //!
        static pointer_type create(const string &format);
};
