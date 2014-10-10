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
// Created on: Oct 8,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include "detector_info.hpp"

//!
//! \brief output formatting
//! 
//! This abstract class defines the interface for output formatters. 
//! Those classes are used to represent the output of detinfo in various 
//! formats.
//! 
class output_formatter
{
    public:
        //!
        //! \brief global header
        //! 
        //! This function is called once at the begining of the processing
        //! sequence. 
        //! 
        //! \param stream the output stream
        //! \sa footer
        //!
        virtual void header(std::ostream &stream) = 0;

        //--------------------------------------------------------------------
        //! 
        //! \brief global footer
        //! 
        //! This function is called once at the end of the processing sequence. 
        //! 
        //! \param stream the output stream
        //! \sa header
        //!
        virtual void footer(std::ostream &stream) = 0;

        //--------------------------------------------------------------------
        //!
        //! \brief detector header
        //! 
        //! This function is called right before detector data is written. 
        //! 
        //! \param stream output stream
        //! \sa detector_footer
        //!
        virtual void detector_header(std::ostream &stream) = 0;

        //--------------------------------------------------------------------
        //!
        //! \brief detector footer
        //!
        //! This function is called after detector data is written.
        //!
        //! \param stream output stream
        //! \sa detector_header
        //!
        virtual void detector_footer(std::ostream &stream) = 0;
        
        //---------------------------------------------------------------------
        //!
        //! \breif write detector information
        //!
        //! This function writes the detector information in the 
        //! desired format. 
        //!
        //! \param stream output stream
        //! \param info detector information object
        //! 
        virtual void write(std::ostream &stream,const detector_info &info) = 0;
};

std::ostream &operator<<(std::ostream &stream,const shape_t &shape);

