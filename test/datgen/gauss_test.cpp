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
#define BOOST_TEST_MODULE gauss function test for datgen
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

#include <test/config.hpp>
#include <test/command_runner.hpp>
#include "datgen_fixture.hpp"
#include <cmath>

using namespace pni::core;

const float64 PI = std::acos(-1.0);

class gauss
{
    private:
        float64 _amplitude;
        float64 _sigma;
        float64 _mu;
    public:
        gauss(float64 a,float64 s,float64 m):
            _amplitude(a),
            _sigma(s),
            _mu(m)
        {}

        float64 operator()(float64 x)
        {
            float64 a = -0.5*std::pow((x-_mu)/_sigma,2);
            float64 p = _amplitude/_sigma/std::sqrt(2*PI);
            return p*std::exp(a);
        }
};


struct gauss_test_fixture : public datgen_fixture
{
    cmd_opts_t options;

    gauss_test_fixture():
        datgen_fixture(),
        options({"-b100","-e200","-s4","--show-grid","gauss"})
    {}

    int run_test(const cmd_opts_t &opts)
    {
        options.insert(options.end(),opts.begin(),opts.end());
        return runner(options);
    }
};

BOOST_FIXTURE_TEST_SUITE(datgen_gauss_test,gauss_test_fixture)

    BOOST_AUTO_TEST_CASE(test_sigma_fail)
    {
        BOOST_CHECK_EQUAL(run_test({"-s1.x"}),1);
    }

    BOOST_AUTO_TEST_CASE(test_mu_fail)
    {
        BOOST_CHECK_EQUAL(run_test({"-m1x"}),1);
    }
    
    BOOST_AUTO_TEST_CASE(test_amplitude_fail)
    {
        BOOST_CHECK_EQUAL(run_test({"-a1u"}),1);

    }

    BOOST_AUTO_TEST_CASE(test_ok)
    {
        BOOST_CHECK_EQUAL(run_test({"-a5.","-s2","-m0.5"}),0);
        read_results();

        gauss g(5,2,0.5);

        for(auto x_iter = x.begin(),y_iter = y.begin(); x_iter!=x.end();
                ++x_iter,++y_iter)
        {
            BOOST_CHECK_CLOSE(*y_iter,g(*x_iter),0.001);
        }

    }



BOOST_AUTO_TEST_SUITE_END()
