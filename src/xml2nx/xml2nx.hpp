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
 * Created on: Jun 10, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include<iostream>

#include <pni/core/types.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/nxvariant.hpp>


using namespace pni::core;
using namespace pni::io::nx;

//define a general object type for HDF5 objects
typedef nxvariant_traits<h5::nxfile>::object_types nxobject_t;

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create program configuration

Create the configuration object for xml2nx. 
\return configuration instance
*/
configuration create_config();

//-----------------------------------------------------------------------------
/*!
\ingroup xml2nx_devel
\brief create/open the nexus file

\param path Nexus path object
\param overwrite true if the file should be rewritten
\return instance of nxfile
*/
h5::nxfile open_nexus_file(const nxpath &path,bool overwrite);
