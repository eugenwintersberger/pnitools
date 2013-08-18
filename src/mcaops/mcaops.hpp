/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: May 10,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<iostream>
#include<memory>
#include<map>

#include<pni/core/types.hpp>
#include<pni/core/darray.hpp>
#include<pni/core/numarray.hpp>
#include<pni/core/config/configuration.hpp>
#include<pni/core/config/config_parser.hpp>
#include<pni/io/fio/fio_reader.hpp>

#include "operation.hpp"
#include "max_operation.hpp"
#include "sum_operation.hpp" 
#include "rebin_operation.hpp"
#include "scale_operation.hpp"
#include "dump_operation.hpp"
#include "io.hpp"


using namespace pni::core;
using namespace pni::io;


/*!
\ingroup mcaops_devel
\brief  pointer type for operations
*/
typedef std::unique_ptr<operation> op_ptr;

/*!
\ingroup mcaops_devel
\brief select and configure operator

This function selects the proper operator and configures it according to the
command line options passed by the user. 
\param config global configuration options
\param scale_config configuration options for the scale operator
\param rebin_config configuration options for the rebin operator
*/
op_ptr select_operator(const configuration &config,
                       const configuration &cmd_config);

