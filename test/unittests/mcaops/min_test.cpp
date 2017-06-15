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
// ===========================================================================
//  Created on: Jun 10, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "operations_test_common.hpp"
#include <mcaops/operations/min.hpp>

using namespace pni::core;
using boost::test_tools::output_test_stream;

struct fixture_min
{
    shape_t shape;
    array_type channels;
    array_type data_1;
    array_type data_2;
    array_type data_3;
    min op;
    output_test_stream stream;

    fixture_min():
        shape(shape_t{4}),
        channels(array_type::create(shape,storage_type{0,1,2,3})),
        data_1(array_type::create(shape,
                    storage_type{1.,-5.39,10.3948,9.739 })),
        data_2(array_type::create(shape,
                    storage_type{1000.023,-234,4.20,1000.0})),
        data_3(array_type::create(shape,
                    storage_type{1000.2323,83,-23e-2,1000000})),
        op(),
        stream()
    {}
};

BOOST_FIXTURE_TEST_SUITE(min_test,fixture_min)

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_1)
{
    argument_type arg{{channels.begin(),channels.end()},
                      {data_1.begin(),data_1.end()}};
    op(arg);
    op.stream_result(stream);
    BOOST_CHECK(stream.is_equal("-5.390000e+00"));
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_2)
{
    argument_type arg{{channels.begin(),channels.end()},
                      {data_2.begin(),data_2.end()}};
    op(arg);
    op.stream_result(stream);
    BOOST_CHECK(stream.is_equal("-2.340000e+02"));
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_3)
{
    argument_type arg{{channels.begin(),channels.end()},
                      {data_3.begin(),data_3.end()}};
    op(arg);
    op.stream_result(stream);
    BOOST_CHECK(stream.is_equal("-2.300000e-01"));
}

BOOST_AUTO_TEST_SUITE_END()




//-----------------------------------------------------------------------------
    /*
void max_operation_test::test_max_static()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    double value = 0.0;
    size_t pos = 0;
    max_operation op;
    op(channel_1,data_1);
    get_result(op,pos,value);
    CPPUNIT_ASSERT(pos == 2);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,10.3948,1.e-8);

    op(channel_2,data_2);
    get_result(op,pos,value);
    CPPUNIT_ASSERT(pos == 0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,1000.023,1.e-8);

    op(channel_3,data_3);
    get_result(op,pos,value);
    CPPUNIT_ASSERT(pos == 3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,1000000,1.e-8);
}
*/
