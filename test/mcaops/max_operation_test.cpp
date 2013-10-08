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
 *  Created on: Oct 8, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <vector>
#include <list>
#include <sstream>
#include <algorithm>

#include "max_operation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(max_operation_test);

void max_operation_test::load_data(const vector_t &c,const vector_t &d)
{
    channels = array_type(shape_t{c.size()});
    data     = array_type(shape_t{d.size()});

    std::copy(std::begin(c),std::end(c),std::begin(channels));
    std::copy(std::begin(d),std::end(d),std::begin(data));
}

//-----------------------------------------------------------------------------
void max_operation_test::get_result(operation &op,size_t &pos,double &value)
{
    std::stringstream ss;
    ss<<op;
    ss>>pos>>value;
}

//-----------------------------------------------------------------------------
void max_operation_test::setUp() 
{
    ref_data_1 = {1., -5.39, 10.3948, 9.739 };
    ref_data_2 = {1000.023, -234,4.20,1000.0};
    ref_data_3 = {1000.2323,83,-23e-2,1000000};
}
//-----------------------------------------------------------------------------
void max_operation_test::tearDown() {}

//-----------------------------------------------------------------------------
void max_operation_test::test_max_static()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    double value = 0.0;
    size_t pos = 0;
    max_operation op;
    load_data(ref_data_1,ref_data_1);
    op(channels,data);
    get_result(op,pos,value);
    CPPUNIT_ASSERT(pos == 2);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,10.3948,1.e-8);

    load_data(ref_data_2,ref_data_2);
    op(channels,data);
    get_result(op,pos,value);
    CPPUNIT_ASSERT(pos == 0);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,1000.023,1.e-8);
    
    load_data(ref_data_3,ref_data_3);
    op(channels,data);
    get_result(op,pos,value);
    CPPUNIT_ASSERT(pos == 3);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(value,1000000,1.e-8);
}

