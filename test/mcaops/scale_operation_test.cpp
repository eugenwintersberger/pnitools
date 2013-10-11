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
#include <iomanip>
#include <limits>

#include "scale_operation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scale_operation_test);

float64 scale_operation_test::compute_axis(float64 cv,size_t i,float64 d,size_t cb)
{
    return cv + d*(float64(i)-float64(cb));
}

void scale_operation_test::load_data(const vector_t &c,const vector_t &d)
{
    channels = array_type(shape_t{c.size()});
    data     = array_type(shape_t{d.size()});

    std::copy(std::begin(c),std::end(c),std::begin(channels));
    std::copy(std::begin(d),std::end(d),std::begin(data));
}

//-----------------------------------------------------------------------------
void scale_operation_test::get_result(operation &op,vector_t &axis)
{
    std::stringstream ss;
    ss<<op;
    double c,d;
   
    axis = vector_t();
    while(!ss.eof())
    {
        ss>>c>>d;
        axis.push_back(c);
    }
}

//-----------------------------------------------------------------------------
scale_operation_test::array_type
 scale_operation_test::generate_channel_data(size_t start,size_t stop)
{
    array_type v(shape_t{stop-start});

    for(size_t i=start;i<stop;++i) v[i] = i;

    return v;
}

//-----------------------------------------------------------------------------
void scale_operation_test::setUp() { }
//-----------------------------------------------------------------------------
void scale_operation_test::tearDown() {}

//-----------------------------------------------------------------------------
void scale_operation_test::test_configuration()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    scale_operation op;
    CPPUNIT_ASSERT(op.center_bin() == 0);
    CPPUNIT_ASSERT(op.use_data_maximum());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(op.delta(),1.0,1.e-16);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(op.center_value(),0.0,1.e-16);
    
    //testing set and get methods
    op.center_bin(100);
    CPPUNIT_ASSERT(op.center_bin() == 100);
    op.use_data_maximum(true);
    CPPUNIT_ASSERT(op.use_data_maximum());
    op.delta(-23.3221);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(op.delta(),-23.3221,1.e-8);
    op.center_value(2.34e-4);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(op.center_value(),2.34e-4,1.e-8);
}

//-----------------------------------------------------------------------------
void scale_operation_test::test_exceptions()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //----------------check for size mismatch----------------------------------
    array_type d1(shape_t{10});
    array_type c1(shape_t{20});
    size_t i=0;
    for(auto &c: c1) c=i++;

    scale_operation op;
    CPPUNIT_ASSERT_THROW(op(c1,d1),size_mismatch_error);
   
    //-------------------check for shape mismatch------------------------------
    array_type d2 = array_type(shape_t{4,5});
    array_type c2 = array_type(shape_t{2,5});
    i = 0;
    for(auto &c: c2) c = i++;
    CPPUNIT_ASSERT_THROW(op(c1,d2),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(op(c2,d1),shape_mismatch_error);

}

//-----------------------------------------------------------------------------
void scale_operation_test::test_automax()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    vector_t axis;
    channels = generate_channel_data(0,48);
    data = array_type(channels.shape<shape_t>());
    std::fill(std::begin(data),std::end(data),0);
    data[20] = 100;

    scale_operation op;

    op.delta(0.5);
    op.center_value(1.34);
    op(channels,data);
    CPPUNIT_ASSERT(op.center_bin() == 20);
    
    get_result(op,axis);
    for(auto c: channels)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(axis[c],compute_axis(1.34,c,0.5,20),1.e-8);

}

//-----------------------------------------------------------------------------
void scale_operation_test::test_usermax()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    vector_t axis;
    channels = generate_channel_data(0,48);
    data = array_type(channels.shape<shape_t>());
    std::fill(std::begin(data),std::end(data),0);

    scale_operation op;

    op.delta(0.5);
    op.center_value(1.34);
    op.center_bin(30);
    op.use_data_maximum(false); //switch of automatic maximum search
    op(channels,data);
    CPPUNIT_ASSERT(op.center_bin() == 30);
    
    get_result(op,axis);
    for(auto c: channels)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(axis[c],compute_axis(1.34,c,0.5,30),1.e-8);

}
