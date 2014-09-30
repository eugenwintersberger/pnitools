//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// =========================================================================
//  Created on: Oct 8, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "../test_utils.hpp"
#include "scale_operation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scale_operation_test);

//-----------------------------------------------------------------------------
float64 scale_operation_test::compute_axis(float64 cv,size_t i,float64 d,
                                           size_t cb)
{
    return cv + d*(float64(i)-float64(cb));
}

//-----------------------------------------------------------------------------
void scale_operation_test::get_result(operation &op,array_type &axis)
{
    std::vector<value_type> data;
    std::stringstream ss;
    ss<<op;
    value_type c,d;
   
    while(ss>>c>>d) data.push_back(c);

    axis = array_type::create(shape_t({data.size()}));
    std::copy(data.begin(),data.end(),axis.begin());
}


//-----------------------------------------------------------------------------
void scale_operation_test::setUp() 
{ 
    shape = shape_t{{nchannels}};

    //---------------setup the different channel indices-----------------------
    channels_1 = array_type::create(shape);
    channels_2 = array_type::create(shape);

    create_range(channels_1.begin(),channels_1.end(),0,1);
    create_range(channels_2.begin(),channels_2.end(),3,1);

    //---------------------setup the data array--------------------------------
    data = array_type::create(shape);
    std::fill(data.begin(),data.end(),0.0);

}
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
    auto d1 = array_type::create(shape_t({10}));
    auto c1 = array_type::create(shape_t({20}));
    size_t i=0;
    for(auto &c: c1) c=i++;

    scale_operation op;
    CPPUNIT_ASSERT_THROW(op(c1,d1),size_mismatch_error);
   
    //-------------------check for shape mismatch------------------------------
    auto d2 = array_type::create(shape_t({4,5}));
    auto c2 = array_type::create(shape_t({2,5}));
    i = 0;
    for(auto &c: c2) c = i++;
    CPPUNIT_ASSERT_THROW(op(c1,d2),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(op(c2,d1),shape_mismatch_error);
}

//-----------------------------------------------------------------------------
void scale_operation_test::test_automax()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    //set the data maximum to index 20 
    data[20] = 100;

    //setup the scale operator
    scale_operation op;
    op.delta(0.5);
    op.center_value(1.34);

    //test with 0-based channel indexes
    op(channels_1,data);
    CPPUNIT_ASSERT(op.center_bin() == 20);
   
    array_type axis;
    get_result(op,axis);
    for(auto c: channels_1)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(axis[c],compute_axis(1.34,c,0.5,20),1.e-8);

    //test with 3 based channel indexes
    op(channels_2,data);
    CPPUNIT_ASSERT(op.center_bin() == 23);
    get_result(op,axis);
    for(auto c: channels_2)
        //need to fix here the index c-3 as the index is not the correct array
        //index
        CPPUNIT_ASSERT_DOUBLES_EQUAL(axis[c-3],compute_axis(1.34,c,0.5,23),1.e-8);

}

//-----------------------------------------------------------------------------
void scale_operation_test::test_usermax()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    //setup the scale operator
    scale_operation op;
    op.delta(0.5);
    op.center_value(1.34);
    op.center_bin(30);
    op.use_data_maximum(false); //switch of automatic maximum search

    //test with 0-based channel indexes
    op(channels_1,data);
    CPPUNIT_ASSERT(op.center_bin() == 30);
   
    array_type axis;
    get_result(op,axis);
    for(auto c: channels_1)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(axis[c],compute_axis(1.34,c,0.5,30),1.e-8);

    //test with 3-based channel indexes
    op(channels_2,data);
    CPPUNIT_ASSERT(op.center_bin() == 30);
   
    get_result(op,axis);
    for(auto c: channels_2)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(axis[c-3],compute_axis(1.34,c,0.5,30),1.e-8);

}
