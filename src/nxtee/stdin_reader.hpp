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

#include <vector>
#include <pni/io/parsers.hpp>
#include <pni/core/types.hpp>

//!
//! \ingroup nxtee_devel
//! \brief reads data from standard input
//! 
//! Reads data items and returns every newly parsed input line with next().
//! 
template<typename T> class stdin_reader
{
    public:
        //! value type
        typedef T value_type;
        //! buffer type used to keep results
        typedef std::vector<value_type> buffer_type;
        //! iterator type to create the parser type
        typedef pni::core::string::const_iterator iterator_type;
        //! parser type
        typedef pni::io::parser<iterator_type,buffer_type> parser_type;
    private:
        //! local line storage
        pni::core::string _line_buffer;
        //! local parser instance
        parser_type _parser;
    public:

        //!
        //! \brief read next line
        //! 
        //! Reads the next line from standard input. If no line could be
        //! this function returns false. In case of success true is returned.
        //! The parser result is stored in the buffer provided by the user. 
        //! 
        //! \param buffer reference to the users data buffer
        //! \return true on success, false otherwise
        //!
        bool next(buffer_type &buffer)
        {
            if(!std::getline(std::cin,_line_buffer,'\n'))
                return false;
    
            buffer = _parser(_line_buffer);
            return true;
        }
        
};
