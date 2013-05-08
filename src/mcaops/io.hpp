/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: May 08,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <vector>

#include "operation.hpp"

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
\brief create channel data

\param n number of channels
*/
operation::array_type create_channel_data(size_t n);
