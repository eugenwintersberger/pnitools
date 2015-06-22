//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Oct 7, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <sstream>

#include <common/roi.hpp>

using namespace pni::core;

typedef dynamic_array<int64> array_type;

struct roi_fixture
{
    roi_type roi_1;
    roi_type roi_2;
    roi_type roi_3;
    roi_type r;
    array_type a;

    roi_fixture():
        roi_1(roi_type{slice(0)}),
        roi_2(roi_type{slice(10),slice(0,100)}),
        roi_3(roi_type{slice(5,20),slice(20),slice(1024)}),
        a(array_type::create(shape_t{100})),
        r()
    {
        std::iota(a.begin(),a.end(),0); 
    }
};


BOOST_FIXTURE_TEST_SUITE(roi_test,roi_fixture)

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rank)
{
    BOOST_CHECK_EQUAL(rank(roi_1),1);
    BOOST_CHECK_EQUAL(rank(roi_2),2);
    BOOST_CHECK_EQUAL(rank(roi_3),3);

}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_size)
{
    BOOST_CHECK_EQUAL(size(roi_1),1);
    BOOST_CHECK_EQUAL(size(roi_2),100);
    BOOST_CHECK_EQUAL(size(roi_3),15);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_input_1d)
{
    std::stringstream s("10");
    s>>r;
    BOOST_CHECK_EQUAL(size(r),1);
    BOOST_CHECK_EQUAL(rank(r),1);
    BOOST_CHECK_EQUAL(r[0].first(),10);
    BOOST_CHECK_EQUAL(r[0].last(),11);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_input_2d)
{
    std::stringstream s("10:100,3:5");
    s>>r;
    BOOST_CHECK_EQUAL(size(r),90*2);
    BOOST_CHECK_EQUAL(rank(r),2);
    BOOST_CHECK_EQUAL(r[0],slice(10,100));
    BOOST_CHECK_EQUAL(r[1],slice(3,5));
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_input_3d)
{
    std::stringstream s("10:100,34,100:200");
    s>>r;
    BOOST_CHECK_EQUAL(size(r),90*100);
    BOOST_CHECK_EQUAL(rank(r),3);
    BOOST_CHECK_EQUAL(r[0],slice(10,100));
    BOOST_CHECK_EQUAL(r[1],slice(34));
    BOOST_CHECK_EQUAL(r[2],slice(100,200));
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_apply_1)
{
    r = roi_type{slice(10,20)};
    auto first = a.begin();
    auto last  = a.end();
    apply_roi_to_iterators(r,first,last);

    BOOST_CHECK_EQUAL(*first,9);
    BOOST_CHECK_EQUAL(*last,19);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_apply_2)
{
    r = roi_type{slice(50,51)};
    auto first = a.begin();
    auto last  = a.end();
    apply_roi_to_iterators(r,first,last);

    BOOST_CHECK_EQUAL(*first,49);
    BOOST_CHECK_EQUAL(*last,50);
}

//----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()




