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
// Created on: Jun 5,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>

//!
//! \ingroup common_devel
//! \brief check for help request
//! 
//! Checks if the configuration passed to this function includes a help 
//! request and returns true if this is the case. The function assumes that 
//! the configuration has a boolean option named "help". 
/*!
\code{.cpp} 
configuration config;
config.add_option(config_option<bool>("help","h","show help text",false));

... code omitted ...;

if(check_help_request(config,"Program usage")) return 1;
\endcode
*/
//! \param config the configuration to check
//! \param header the header string for the output
//! \return true if the user requested help
//!
bool check_help_request(const pni::core::configuration &config,
                        const pni::core::string &header);

//-----------------------------------------------------------------------------
//!
//! \ingroup common_devel
//! \brief parse CLI options
//! 
//! This function parsers the command line options provided by the user and 
//! stores the results in config. If an error occurs the function return true, 
//! false otherwise. 
/*!
\code{.cpp}
int main(int argc,char **argv)
{
    configuration config;

    ... code omitted ...;

    if(parse_cli_opts(argc,argv,"test_program",config)) return 1;


    ... code omitted ...;

    return 0;
}
\endcode
*/
//! \param argc number of CLI arguments
//! \param argv holds argument values
//! \param progname name of the program (required for error output)
//! \param config instance of configuration where to store the data
//! \return true in case of errors, false otherwise
//!
bool parse_cli_opts(int argc,char **argv,const pni::core::string &progname,
                    pni::core::configuration &config);
