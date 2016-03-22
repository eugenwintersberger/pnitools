//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
//  Created on: Mar 22, 2016
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <pni/core/types.hpp>
#include <vector>
#include <sstream>

#include <common/algorithms/average.hpp>

using namespace pni::core;
using namespace algorithms;

using vector_type = std::vector<float64>;

BOOST_AUTO_TEST_SUITE(average_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_1)
    {
        vector_type v{1.,2.,3.,4.};
        auto result = average(v.begin(),v.end());
        BOOST_CHECK_CLOSE(result,float64(10.0)/float64(v.size()),1.e-10);
    }

    BOOST_AUTO_TEST_CASE(test_2)
    {
        vector_type v{-20.23,203.12,492.2};
        auto result = average(v.begin(),v.end());
        BOOST_CHECK_CLOSE(result,float64(675.09)/float64(v.size()),1.e-10);

    }

BOOST_AUTO_TEST_SUITE_END()
