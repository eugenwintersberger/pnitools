/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jun 26, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "array_utils_test.hpp"

#define CREATE_TEST(tid)\
    a = create_array(tid,shape); \
    CPPUNIT_ASSERT(a.type_id() == tid); \
    check_shape();\
    CPPUNIT_ASSERT(a.rank() == 3)

CPPUNIT_TEST_SUITE_REGISTRATION(array_utils_test);

//-----------------------------------------------------------------------------
void array_utils_test::setUp()
{
    shape = shape_t{1,3,4};
}

//-----------------------------------------------------------------------------
void array_utils_test::tearDown() { }

//-----------------------------------------------------------------------------
void array_utils_test::check_shape()
{
    auto ashape = a.shape<shape_t>();

    auto siter = shape.begin();
    auto aiter = ashape.begin();

    for(; siter!=shape.end();++siter,++aiter)
        CPPUNIT_ASSERT(*siter == *aiter);

}

//-----------------------------------------------------------------------------
void array_utils_test::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CREATE_TEST(type_id_t::UINT8);
    CREATE_TEST(type_id_t::INT8);
    CREATE_TEST(type_id_t::UINT16);
    CREATE_TEST(type_id_t::INT16);
    CREATE_TEST(type_id_t::UINT32);
    CREATE_TEST(type_id_t::INT32);
    CREATE_TEST(type_id_t::UINT64);
    CREATE_TEST(type_id_t::INT64);

    CREATE_TEST(type_id_t::FLOAT32);
    CREATE_TEST(type_id_t::FLOAT64);
    CREATE_TEST(type_id_t::FLOAT128);

    CPPUNIT_ASSERT_THROW(create_array(type_id_t::COMPLEX32,shape),
                         type_error);
}
