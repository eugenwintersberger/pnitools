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
// Created on: Jun 10, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include<iostream>

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include <pni/io/nexus.hpp>

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create program configuration

Create the configuration object for xml2nx. 
\return configuration instance
*/
pni::core::configuration create_config();

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create/open the nexus file

\param path Nexus path object
\param overwrite true if the file should be rewritten
\return instance of nxfile
*/
hdf5::file::File open_nexus_file(const pni::io::nexus::Path &path,bool overwrite);
