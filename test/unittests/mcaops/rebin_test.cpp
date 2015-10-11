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

#include "operations_test_common.hpp"
#include <mcaops/operations/rebin.hpp>

using namespace pni::core;
using boost::test_tools::output_test_stream;

struct rebin_fixture
{
    shape_t shape;
    array_type mca;
    array_type channels;
    output_test_stream stream;

    rebin_fixture():
        shape(shape_t{48}),
        mca(array_type::create(shape,
                    storage_type{45, 13, 52, 51, 51, 62, 69, 83, 41, 41,
                                     49, 58, 84, 36, 42,  0, 50, 25, 71, 68,
                                      0,  8, 49, 34, 25, 56, 85, 80, 33, 56, 
                                      3, 56, 95, 63, 33, 42, 24, 32, 92, 35, 
                                     57, 38, 30, 90, 31, 75, 17, 63})),
        channels(array_type::create(shape)),
        stream()
    {
        std::iota(channels.begin(),channels.end(),0);
    }

};

BOOST_FIXTURE_TEST_SUITE(rebin_test,rebin_fixture)


//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rebin_no_x_no_norm)
{
    rebin op;
    op.configure(args_vector{"-b10","--noxrebin"});
    argument_type arg{{channels.begin(),channels.end(),
                      mca.begin(),mca.end()}};
    op(arg);
    op.stream_result(stream);

    string result= "0\t508.0\n1\n483.0\n"
                   "2\t426.0\n3\n475.0\n"
                   "4\t401.0";

    BOOST_CHECK(stream.is_equal(result));
}

//-----------------------------------------------------------------------------
/*
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
*/
//-----------------------------------------------------------------------------
/*
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
*/

BOOST_AUTO_TEST_SUITE_END()



