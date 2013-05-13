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
#include<pni/io/fio_reader.hpp>

#include "operation.hpp"
#include "max_operation.hpp"
#include "sum_operation.hpp" 
#include "rebin_operation.hpp"
#include "scale_operation.hpp"
#include "io.hpp"


using namespace pni::core;
using namespace pni::io;

typedef std::map<string,configuration> cmd_config_registry_t;

static const cmd_config_registry_t cmd_config_registry =
 {{"max",configuration()},
  {"sum",configuration()},
  {"rebin",configuration()},
  {"scale",configuration()}};


typedef std::unique_ptr<operation> op_ptr;
