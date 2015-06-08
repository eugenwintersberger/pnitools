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
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <datgen/grid_generator.hpp>

using namespace pni::core;

BOOST_AUTO_TEST_SUITE(grid_generator_test)

static float64 tolerance = 1.e-8;

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_creation_default)
{
    grid_generator g;
    BOOST_CHECK_CLOSE(g(),0.0,tolerance);
    BOOST_CHECK_CLOSE(g(),0.0,tolerance);
    BOOST_CHECK_CLOSE(g(),0.0,tolerance);
    BOOST_CHECK_CLOSE(g(),0.0,tolerance);
}

BOOST_AUTO_TEST_CASE(test_creation_1)
{
    grid_generator g(10.,1.2);
    BOOST_CHECK_CLOSE(g(),10.0,tolerance);
    BOOST_CHECK_CLOSE(g(),11.2,tolerance);
    BOOST_CHECK_CLOSE(g(),12.4,tolerance);
    BOOST_CHECK_CLOSE(g(),13.6,tolerance);

}

BOOST_AUTO_TEST_SUITE_END()
