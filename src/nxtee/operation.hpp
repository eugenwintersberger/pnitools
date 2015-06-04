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
//************************************************************************
// Created on: Jun 3, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nx/nx.hpp>


//!
//! \ingroup nxtee_devel
//! \brief append data to target
//! 
//! Appends data to the target object
//! 
//! \param target the object to which to append data
//! 
void append(pni::io::nx::h5::nxobject &target);

//!
//! \ingroup nxtee_devel
//! \brief replace data
//! 
//! Replaces data with content from standard input.
//! 
//! \param target the object into which data should be replaced
//! \param offset index offset where to start with replacement
//!
void replace(pni::io::nx::h5::nxobject &target,size_t index_offset);


