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
// ===========================================================================
//  Created on: Oct 11, 2013
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

#include "rebin_operation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(rebin_operation_test);


//-----------------------------------------------------------------------------
void rebin_operation_test::get_result(operation &op,array_type &axis,
                                      array_type &data)
{
    std::vector<value_type> c_v,d_v;
    std::stringstream ss;
    ss<<op;
    value_type c,d;
   
    while(ss>>c>>d) 
    {
        c_v.push_back(c);
        d_v.push_back(d);
    }

    axis = array_type::create(shape_t({c_v.size()}));
    data = array_type::create(shape_t({d_v.size()}));

    std::copy(c_v.begin(),c_v.end(),axis.begin());
    std::copy(d_v.begin(),d_v.end(),data.begin());
}


//-----------------------------------------------------------------------------
void rebin_operation_test::setUp() 
{ 
    shape = shape_t{nchannels};
    std::vector<value_type> rdata = {45, 13, 52, 51, 51, 62, 69, 83, 41, 41,
                                     49, 58, 84, 36, 42,  0, 50, 25, 71, 68,
                                      0,  8, 49, 34, 25, 56, 85, 80, 33, 56, 
                                      3, 56, 95, 63, 33, 42, 24, 32, 92, 35, 
                                     57, 38, 30, 90, 31, 75, 17, 63};

    //---------------setup the different channel indices-----------------------
    channels_1 = array_type::create(shape);
    channels_2 = array_type::create(shape);

    create_range(channels_1.begin(),channels_1.end(),0,1);
    create_range(channels_2.begin(),channels_2.end(),3,1);

    //---------------------setup the data array--------------------------------
    data = array_type::create(shape);
    std::copy(rdata.begin(),rdata.end(),data.begin());

}
//-----------------------------------------------------------------------------
void rebin_operation_test::tearDown() {}

//-----------------------------------------------------------------------------
void rebin_operation_test::test_configuration()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //check default configuration
    rebin_operation op;
    CPPUNIT_ASSERT(op.bin_size() == 0);
    CPPUNIT_ASSERT(!op.no_x_rebinning());
    CPPUNIT_ASSERT(!op.normalization());
}

//-----------------------------------------------------------------------------
void rebin_operation_test::test_set_get()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    rebin_operation op;

    op.bin_size(10);
    CPPUNIT_ASSERT(op.bin_size() == 10);
    op.normalization(true);
    CPPUNIT_ASSERT(op.normalization());
    op.no_x_rebinning(true);
    CPPUNIT_ASSERT(op.no_x_rebinning());
}

//-----------------------------------------------------------------------------
void rebin_operation_test::test_rebin_no_x_no_norm()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    

    rebin_operation op;
    op.bin_size(10);
    op.no_x_rebinning(true);
    op(channels_1,data);
    array_type rdata,rchannels;
    get_result(op,rchannels,rdata);
    CPPUNIT_ASSERT(rdata.size() == 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[0],508.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[1],483.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[2],426.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[3],475.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[4],401.0,1.e-8);
    CPPUNIT_ASSERT(rchannels.size() == 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[0],0.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[1],1.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[2],2.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[3],3.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[4],4.0,1.e-8);

    
}

//-----------------------------------------------------------------------------
void rebin_operation_test::test_rebin_no_x_norm()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    rebin_operation op;
    op.bin_size(10);
    op.normalization(true);
    op.no_x_rebinning(true);
    op(channels_1,data);
    array_type rdata,rchannels;
    get_result(op,rchannels,rdata);
    CPPUNIT_ASSERT(rdata.size() == 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[0],508.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[1],483.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[2],426.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[3],475.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[4],401.0/8.,1.e-8);
    CPPUNIT_ASSERT(rchannels.size() == 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[0],0.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[1],1.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[2],2.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[3],3.0,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[4],4.0,1.e-8);
}

//-----------------------------------------------------------------------------
void rebin_operation_test::test_rebin_x_norm()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    rebin_operation op;
    op.bin_size(10);
    op.normalization(true);
    op.no_x_rebinning(false);
    op(channels_1,data);
    array_type rdata,rchannels;
    get_result(op,rchannels,rdata);
    CPPUNIT_ASSERT(rdata.size() == 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[0],508.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[1],483.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[2],426.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[3],475.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rdata[4],401.0/8.,1.e-8);
    CPPUNIT_ASSERT(rchannels.size() == 5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[0],45.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[1],145.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[2],245.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[3],345.0/10.,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(rchannels[4],348.0/8.,1.e-8);
}



