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

#include "stdin_reader.hpp"
#include "selection.hpp"
#include "utils.hpp"

#include <pni/io/nexus.hpp>


//!
//! \ingroup nxtee_devel
//! \brief append data to a target
//! 
//! The target object must be a field instance as one cannot grow 
//! attributes. The data is appended along the first dimension of the 
//! field.
//! 
//! \tparam T data type to process
//! 
template<typename T> class Appender
{
  private:
    //! reader type
    using ReaderType =  StandardInputReader<T>;
    //! local data buffer instance
    typename ReaderType::BufferType _buffer;
    //! local reader instance
    ReaderType _reader;

    void write(const hdf5::node::Dataset &dataset)
    {
      hdf5::dataspace::Hyperslab selection = Selection::create(dataset);

      while(_reader.next(_buffer))
      {
        dataset.extent(0,1);
        dataset.write(_buffer,selection);
        selection.offset(0,selection.offset()[0]+1);
      }
    }

    void write(const hdf5::attribute::Attribute &attribute)
    {
      while(_reader.next(_buffer))
      {
        _reader.next(_buffer);
        attribute.write(_buffer);
      }
    }

  public:

    //!
    //! @brief append data to target
    //!
    //! Append data to the target object.
    //!
    //! @throw invalid_object_error if the target is not a valid object
    //! @throw object_error in case of any object related error
    //! @throw io_error in case of an error during IO
    //! @throw type_error if the datatype cannot be handled
    //! @throw memory_not_allocated_error problems with memory allocation
    //! @throw size_mismatch_error buffer and object size do not match
    //!
    //! @param target the object to which to append data
    //!
    void operator()(pni::io::nexus::PathObject &target)
    {
      using namespace pni::core;
      using namespace pni::io;

      if(nexus::is_dataset(target))
      {

        hdf5::node::Dataset dataset = target;
        write(dataset);
      }
      else if(nexus::is_attribute(target))
      {
        hdf5::attribute::Attribute attribute = target;
        write(attribute);
      }
    }
};

