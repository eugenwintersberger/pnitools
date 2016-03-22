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

#include <common/algorithms/rebin.hpp>

using namespace pni::core;
using namespace algorithms;

using vector_type = std::vector<float64>;

BOOST_AUTO_TEST_SUITE(rebin_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_blocksize_is_not_integer_multiple)
    {
        vector_type v{1.,2.,3.,4.,403.2,-34.0,874.32};
        vector_type expected{6.0,4.0+403.2-34.0,874.32};
        vector_type result;
        rebin(v.begin(),v.end(),std::back_inserter(result),3,false);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      expected.begin(),expected.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_blocksize_is_not_integer_multiple_2)
    {
        vector_type v{1.,2.,3.,4.,403.2,-34.0,874.32,4.52};
        vector_type expected{6.0,4.0+403.2-34.0,874.32+4.52};
        vector_type result;
        rebin(v.begin(),v.end(),std::back_inserter(result),3,false);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      expected.begin(),expected.end());
    }
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_blocksize_is_integer_multiple)
    {
        vector_type v{1.,2.,3.,4.,403.2,-34.0};
        vector_type expected{3.0,7.0,403.2-34.0};
        vector_type result;
        rebin(v.begin(),v.end(),std::back_inserter(result),2,false);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      expected.begin(),expected.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_blocksize_is_not_integer_multiple_norm)
    {
        vector_type v{1.,2.,3.,4.,403.2,-34.0,874.32};
        vector_type expected{6.0/3.0,(4.0+403.2-34.0)/3.0,874.32};
        vector_type result;
        rebin(v.begin(),v.end(),std::back_inserter(result),3,true);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      expected.begin(),expected.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_blocksize_is_not_integer_multiple_2_norm)
    {
        vector_type v{1.,2.,3.,4.,403.2,-34.0,874.32,4.52};
        vector_type expected{6.0/3.,(4.0+403.2-34.0)/3.,(874.32+4.52)/2.};
        vector_type result;
        rebin(v.begin(),v.end(),std::back_inserter(result),3,true);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      expected.begin(),expected.end());
    }
    
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_blocksize_is_integer_multiple_norm)
    {
        vector_type v{1.,2.,3.,4.,403.2,-34.0};
        vector_type expected{3.0/2.0,7.0/2.0,(403.2-34.0)/2.0};
        vector_type result;
        rebin(v.begin(),v.end(),std::back_inserter(result),2,true);
        BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(),result.end(),
                                      expected.begin(),expected.end());
    }

BOOST_AUTO_TEST_SUITE_END()


