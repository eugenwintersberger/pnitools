//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: May 08,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <iostream>
#include <vector>

#include <pni/io/fio/fio_reader.hpp>
#include "operation.hpp"

using namespace pni::io;

/*!
\ingroup mcaops_devel
\brief reads two column input

Reads two column input from standard in and stores the result in a vector.
\param channels array with channel data
\param data array with channel data
*/
void read_from_stdin(operation::array_type &channels,
                     operation::array_type &data);

//-----------------------------------------------------------------------------
/*!
\ingroup mcaops_devel
\brief get column list from reader

Get a list with all available columns from a reader instance.
\param reader a FIO reader instance
\return vector with column names
*/
std::vector<string> get_column_list(const fio_reader &reader);

//-----------------------------------------------------------------------------
/*!
\ingroup mcaops_devel
\brief read column from a file

Read a column from a FIO file and return the result as an array type.
\throws key_error if the column does not exist
\throws file_error in case of any other IO error
\param cname name of the column to read
\param reader instance of the FIO reader
\return array with column data
*/
operation::array_type read_column(const string &cname,fio_reader &reader);

//-----------------------------------------------------------------------------
/*!
\ingroup mcaops_devel
\brief read data from file

Read the MCA and channel data from a file. Currently only FIO files are
supported.
\throws file_error if there is an IO error in the file
\thorws key_error if the column names passed by the user are wrong
\param ifile name of the input file
\param channels channel information
\param data MCA data
\param xcolumn optional name of the channel data column
\param ycolumn optional name of the MCA data column
*/
void read_from_file(const string &ifile,operation::array_type &channels,
                    operation::array_type &data,
                    const string &xcol_name = "",
                    const string &ycol_name = "");
         
//-----------------------------------------------------------------------------
/*! 
\ingroup mcaops_devel
\brief create channel data

\param n number of channels
*/
operation::array_type create_channel_data(size_t n);
