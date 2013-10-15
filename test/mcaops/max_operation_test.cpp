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
#include "../test_utils.hpp"

#include "max_operation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(max_operation_test);


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
    //create channel data
    channel_1 = array_type(shape_t{nchannels});
    create_range(channel_1.begin(),channel_1.end(),0,1);
    channel_2 = channel_1;
    channel_3 = channel_1;

    //create payload data
    data_1 = array_type(shape_t{nchannels});
    data_2 = array_type(shape_t{nchannels});
    data_3 = array_type(shape_t{nchannels});

    std::vector<value_type> data = {1., -5.39, 10.3948, 9.739 };
    std::copy(data.begin(),data.end(),data_1.begin());
    data =  {1000.023, -234,4.20,1000.0};
    std::copy(data.begin(),data.end(),data_2.begin());
    data = {1000.2323,83,-23e-2,1000000};
    std::copy(data.begin(),data.end(),data_3.begin());
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

