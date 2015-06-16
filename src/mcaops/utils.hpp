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
// Created on: May 28, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/arrays/slice.hpp>
#include <pni/core/configuration/configuration.hpp>
#include "operations/operation.hpp"


//!
//! \ingroup mcaops_devel
//! \brief read slice from a stream
//! 
//! Operator to read a slice from a stream. This operator is required to use 
//! slices as a possible type for a command line option.
//!
//! We have to define this in namespace std:: in order to make 
//! boost::program_options to work correctly. We do not have to define an 
//! output operator as it is allready defined in pni::core (see slice.hpp). 
//! 
//! A good reference for this can be found in 
//! http://stackoverflow.com/questions/27848995/\
//!        boost-program-options-pair-value
//!
//! \param stream reference to the input stream
//! \param s reference to the slice
//! \return reference to the input stream
//!
namespace std{
    istream &operator>>(istream &stream,pni::core::slice &s);
}


//----------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \brief applay a ROI to a data range
//!
//! This function applies a ROI to a data range. Basically it adjusts the 
//! begin and end iterator according to the ROI. The changes are applied 
//! inplace to the range passed as a non-const reference.
//!
//! \param range the iterator range to which to apply the ROI
//! \param roi the slice instance representing the ROI
//! 
void apply_roi(operation::data_range &range,const pni::core::slice &roi);

//----------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \brief create global configuration
//!
//! Create the global option set for mcaops. 
//!
//! \return configuration instance with global options
//!
pni::core::configuration create_global_config();

//-----------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \brief false if insufficient number of input arguments
//! 
//! Returns false if the number of input arguments is not sufficient (must be 
//! at least two) and prints an error message. 
//!
//! \param argc number of program arguments
//! \return false if argc<2
//!
bool check_argument_count(int argc);

//-----------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \brief true if help was requested
//!
//! Checks if the command line options requested the help output. If this is 
//! the case true will be returned (and the program should terminate).
//!
bool manage_help_request(const pni::core::configuration &c);

//=============================================================================
static const char usage_string[] = 
                      "Program usage:\n\n mcaops <global options> <command>"
                      " <command specific options> [input file]";

static const char command_string[] = 
            "Commands supported by mcaops:\n"
            "  sum\tum over all channels in a spectrum\n"
            "  max\tosition of maximum and its value\n"
            "  rebin\tre-bin the spectrum\n"
            "  scale\tscale the channel numbers to units\n"
            ;
