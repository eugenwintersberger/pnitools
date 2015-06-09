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
#include <vector>
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>
#include <datgen/grid_generator_builder.hpp>
#include <datgen/grid_generator.hpp>
#include <datgen/datgen_utils.hpp>

using namespace pni::core;

typedef std::vector<string> args_vector;

BOOST_AUTO_TEST_SUITE(grid_generator_builder_test)

static float64 tolerance = 1.e-8;

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_creation)
{
    configuration c = create_global_config();
    parse(c,args_vector{"-e1023","-b0","-s4"});
    grid_generator g = grid_generator_builder::build(c);
    BOOST_CHECK_CLOSE(g(),0.0,tolerance);
    BOOST_CHECK_CLOSE(g(),(0.0+1023./3.),tolerance);
    BOOST_CHECK_CLOSE(g(),(0.0+2*1023./3.),tolerance);
    BOOST_CHECK_CLOSE(g(),1023.,tolerance);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_range_error)
{
    configuration c = create_global_config();
    parse(c,args_vector{"-e1","-b10","-s4"});
    BOOST_CHECK_THROW(grid_generator_builder::build(c),range_error);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_missing_begin)
{
    configuration c = create_global_config();
    parse(c,args_vector{"-e100","-s4"});
    BOOST_CHECK_THROW(grid_generator_builder::build(c),cli_option_error);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_missing_end)
{
    configuration c = create_global_config();
    parse(c,args_vector{"-b100","-s4"});
    BOOST_CHECK_THROW(grid_generator_builder::build(c),cli_option_error);
}


BOOST_AUTO_TEST_SUITE_END()
