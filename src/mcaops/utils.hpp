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

#include <pni/core/configuration/configuration.hpp>
#include "operations/operation.hpp"
#include "../common/file_queue.hpp"
#include "../common/roi.hpp"
#include "io/data_provider.hpp"

typedef data_provider::pointer_type provider_ptr;


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

//-----------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \brief retrieve fiel queue from the input arguments provided by the user
//! 
//! The function returns false if there were any errors (in which case the 
//! program should abort). True is returned in case of success. 
//! 
//! \param c reference to the program configuration
//! \param q reference to the file queue
//! \return true in case of success, false otherwise 
//! 
bool get_file_queue(const pni::core::configuration &c,file_queue &q);

//-----------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \brief get ROI from program configuration
//! 
//! Return the ROI from the use configuration. This function returns true on 
//! success and false otherwise. 
//!
//! \param c reference to the program configuration
//! \param r reference to the ROI 
//! \return true if success, false otherwise
//! 
bool get_roi(const pni::core::configuration &c,roi_type &r);

//------------------------------------------------------------------------------
//!
//! \ingroup mcaops_devel
//! \abrief get data provider
//! 
//! Returns the data provider from the file path and the configuration .
//! The function returns true on success, false otherwise. 
//! 
//! \param path reference to the file path
//! \param c reference to the program configuration
//! \param provider reference to the provider 
//! \return true if successful, false otherwise
//! 
bool get_provider(const pni::core::string &path,const pni::core::configuration &c,
                  provider_ptr &provider);

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
