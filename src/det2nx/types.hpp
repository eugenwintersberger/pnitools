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

#include <vector>
#include <list>
#include <pni/core/types.hpp>
#include <pni/io/image_reader.hpp>
#include <pni/io/image_info.hpp>

#include "../common/file.hpp"

using namespace pni::core;
using namespace pni::io;

//! lvector with strings
typedef std::vector<string> string_vector;

//! pointer type for readers
typedef std::unique_ptr<pni::io::image_reader> reader_ptr;

//! list with file objects
typedef std::list<file> file_list;

