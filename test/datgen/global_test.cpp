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

BOOST_FIXTURE_TEST_SUITE(datgen_global_test,datgen_fixture)

    BOOST_AUTO_TEST_CASE(test_noargs_nopts)
    {
        BOOST_CHECK_EQUAL(runner({}),1);
    }

    BOOST_AUTO_TEST_CASE(test_nofunctor)
    {
        BOOST_CHECK_EQUAL(runner({"-b100","-e200","-s2"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_wrong_functor)
    {
        BOOST_CHECK_EQUAL(runner({"-b100","-e200","-s2","uni"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_missing_grid_endpoint)
    {
        BOOST_CHECK_EQUAL(runner({"-b100","-s2","uniform"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_missing_grid_startpoint)
    {
        BOOST_CHECK_EQUAL(runner({"-e100","-s2","uniform"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_missing_grid_steps)
    {
        BOOST_CHECK_EQUAL(runner({"-e100","-b2","uniform"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_grid_end_small_start)
    {
        BOOST_CHECK_EQUAL(runner({"-b100","-e2","-s1","uniform"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_grid)
    {
        BOOST_CHECK_EQUAL(runner({"-b100","-e200","-s10","--show-grid","uniform"}),0);
        read_results();
        BOOST_CHECK_EQUAL(x.size(),10);
        BOOST_CHECK_EQUAL(y.size(),10);
        float64 x_ref=100.; 
        for(auto iter_x = x.begin();iter_x != x.end(); ++iter_x,x_ref+=(200.-100.)/(10.-1.))
        {
            BOOST_CHECK_CLOSE(*iter_x,x_ref,0.001);
        }
        
        
    }



BOOST_AUTO_TEST_SUITE_END()
