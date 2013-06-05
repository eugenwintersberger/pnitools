/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jun 5,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

//include header files
#include <iostream>
#include <pni/core/types.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include <pni/io/nx/nx.hpp>
#include "../common/file.hpp"
#include "../common/file_list.hpp"
#include "../common/exceptions.hpp"
#include <boost/filesystem.hpp> 

//setting namespaces
using namespace pni::io::nx::h5;
using namespace pni::core;
namespace fs = boost::filesystem;

typedef std::vector<string> strlist;

//-----------------utility functions-------------------------------------------
/*!
\ingroup det2nx_devel
\brief create configuration
 
Function creating the program configuration. 
\return instance of config
*/
configuration create_configuration();

//-----------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief create input file list

Creates the list of input files. 
\param fnames list of input file names
\param flist list of input files
\return 0 in case of success, 1 otherwise
*/
int create_input_file_list(const strlist &fnames);

//-----------------------------------------------------------------------------
/*!
\ingroup det2nx_devel
\brief open output file

Opens the file wher the data should be stored. 
\param fname name of the output file
\return an instance of nxfile
*/
nxfile open_output_file(const string &fname);


