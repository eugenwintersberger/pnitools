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
// Created on: Jun 25, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <list>
#include <queue>
#include "file_list_parser.hpp"


//!
//! \ingroup common_devel
//! \brief file queue type 
//!
//! A queue type for file objects. 
typedef std::queue<file,std::list<file>> file_queue;


//! 
//! \ingroup common_devel
//! \brief fill file queue from a name list
//! 
//! Tempalate function which fills a file queue from a container with 
//! file names. These can either be simple file names or file ranges. 
//! 
//! \tparam ICTYPE input container type with file names
//! \param names reference to the name container
//! \return a queue with file objects. 
//! 
template<typename ICTYPE>
file_queue fill_file_queue(const ICTYPE &names)
{
    static_assert(std::is_same<typename ICTYPE::value_type,
                               pni::core::string>::value,
                  "The value type of the input container must be string!");

    return file_queue(file_list_parser::parse<std::list<file>>(names));
}


