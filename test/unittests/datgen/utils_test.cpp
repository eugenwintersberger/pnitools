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
//************************************************************************
//
//  Created on: Jun 8, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <datgen/datgen_utils.hpp>

using namespace pni::core;

BOOST_AUTO_TEST_SUITE(utils_test)

static float64 tolerance = 1.e-8;

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_int)
{
    std::stringstream ss; 
    ss<<"int";
    type_id_t tid;
    ss>>tid;
    BOOST_CHECK_EQUAL(tid,type_id_t::INT64);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_float)
{
    std::stringstream ss;
    ss<<"float";
    type_id_t tid;
    ss>>tid;
    BOOST_CHECK_EQUAL(tid,type_id_t::FLOAT64);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_fail)
{
    std::stringstream ss;
    ss<<"uint16";
    type_id_t tid;
    BOOST_CHECK_THROW(ss>>tid,type_error);
}

BOOST_AUTO_TEST_SUITE_END()
