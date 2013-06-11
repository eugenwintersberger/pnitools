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
 * Created on: Jun 11,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include<iostream>
#include<fstream>
#include<list>
#include<vector>

#include<pni/core/types.hpp>
#include<pni/io/nx/nx.hpp>
#include<pni/io/nx/nxpath.hpp>
#include<pni/io/nx/nxobject_type.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>
#include "../common/nx_object_path.hpp"
#include "../common/field_io.hpp"

using namespace pni::core;
using namespace pni::io::nx;

typedef std::vector<string> string_list;
typedef std::list<nxpath> sources_list;
typedef std::list<array::iterator> record_t;

/*!
\ingroup nxcat_devel
\brief create CLI configuration

Function to create the CLI configuration.
\return configuration object
*/
configuration create_configuration();

//-----------------------------------------------------------------------------
/*!
\ingroup nxcat_devel
\brief extract data from a particular source

Extract the data from a particular source and returns it to the calling program

*/
array read_source(const nxpath &source_path);
