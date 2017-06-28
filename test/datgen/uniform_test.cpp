//
// (c) Copyright 2017 DESY
//
// This file is part of pniio.
//
// pniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pniio.  If not, see <http://www.gnu.org/licenses/>.
// 
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created: Fri 23 Jun, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Global tests for datgen
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

#include <test/config.hpp>
#include <test/command_runner.hpp>
#include "datgen_fixture.hpp"

using namespace pni::core;


struct uniform_test_fixture : public datgen_fixture
{
    cmd_opts_t options;

    uniform_test_fixture():
        datgen_fixture(),
        options({"-b100","-e200","-s2","uniform"})
    {}

    int run_test(const cmd_opts_t &opts)
    {
        options.insert(options.end(),opts.begin(),opts.end());
        return runner(options);
    }
};

BOOST_FIXTURE_TEST_SUITE(datgen_uniform_test,uniform_test_fixture)

    BOOST_AUTO_TEST_CASE(test_ok)
    {
        BOOST_CHECK_EQUAL(run_test({"-l1.2","-u4.5"}),0);
    }

    BOOST_AUTO_TEST_CASE(test_lower_wrong)
    {
        BOOST_CHECK_EQUAL(run_test({"-l1.2x","-u4.5"}),1);
    }
    
    BOOST_AUTO_TEST_CASE(test_upper_wrong)
    {
        BOOST_CHECK_EQUAL(run_test({"-l1.2","-u4.5x"}),1);
    }

#ifndef _MSC_VER
    BOOST_AUTO_TEST_CASE(test_upper_larger_lower)
    {
        BOOST_CHECK_EQUAL(run_test({"-l1.2","-u0.2"}),1);
    }

#endif

BOOST_AUTO_TEST_SUITE_END()
