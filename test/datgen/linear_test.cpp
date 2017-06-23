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
#define BOOST_TEST_MODULE linear function test for datgen
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

#include <test/config.hpp>
#include <test/command_runner.hpp>
#include "datgen_fixture.hpp"

using namespace pni::core;


struct linear_test_fixture : public datgen_fixture
{
    cmd_opts_t options;

    linear_test_fixture():
        datgen_fixture(),
        options({"-b100","-e200","-s4","--show-grid","linear"})
    {}

    int run_test(const cmd_opts_t &opts)
    {
        options.insert(options.end(),opts.begin(),opts.end());
        return runner(options);
    }
};

BOOST_FIXTURE_TEST_SUITE(datgen_linear_test,linear_test_fixture)

    BOOST_AUTO_TEST_CASE(test_wrong_slope)
    {
        BOOST_CHECK_EQUAL(run_test({"-s1.x","-o23."}),1);
    }

    BOOST_AUTO_TEST_CASE(test_offset_wrong)
    {
        BOOST_CHECK_EQUAL(run_test({"-s1","-o2ssx"}),1);
    }
    
    BOOST_AUTO_TEST_CASE(test_ok)
    {
        BOOST_CHECK_EQUAL(run_test({"-s2","-o-4."}),0);
        read_results();

        for(auto x_iter = x.begin(),y_iter = y.begin(); x_iter!=x.end();
                ++x_iter,++y_iter)
        {
            BOOST_CHECK_CLOSE(*y_iter,2.*(*x_iter)-4.,0.001);
        }

    }



BOOST_AUTO_TEST_SUITE_END()
