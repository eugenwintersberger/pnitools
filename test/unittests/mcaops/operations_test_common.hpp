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
//  Created on: Jun 10, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <mcaops/operations/operation.hpp>
#include <pni/core/types.hpp>

typedef operation::array_type    array_type;
typedef array_type::storage_type storage_type;
typedef operation::data_range    data_range;
typedef operation::argument_type argument_type;

