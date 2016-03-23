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
// =========================================================================
//  Created on: Jun 10, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "operations_test_common.hpp"
#include <mcaops/operations/scale.hpp>

using namespace pni::core;
using boost::test_tools::output_test_stream;

struct scale_test_fixture
{
    shape_t shape;
    array_type mca;
    array_type channel_1;
    array_type channel_2;
    output_test_stream stream;

    scale_test_fixture():
        shape(shape_t{48}),
        mca(array_type::create(shape,
                    storage_type{45, 13, 52, 51, 51, 62, 69, 83, 41, 41,
                                     49, 58, 84, 36, 42,  0, 50, 25, 71, 68,
                                      0,  8, 49, 34, 25, 56, 85, 80, 33, 56, 
                                      3, 56, 95, 63, 33, 42, 24, 32, 92, 35, 
                                     57, 38, 30, 90, 31, 75, 17, 63})),
        channel_1(array_type::create(shape)),
        channel_2(array_type::create(shape)),
        stream()
    {
        std::iota(channel_1.begin(),channel_1.end(),0.0);
        std::iota(channel_2.begin(),channel_2.end(),3.0);
    }

};


BOOST_FIXTURE_TEST_SUITE(scale_test,scale_test_fixture)

    float64 compute_axis(float64 cv,size_t i,float64 d,size_t cb)
    {
        cv + d*(float64(i)-float64(cb));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_automax)
    {
        scale op;
        args_vector cnf_opt{"--delta=0.5","--cvalue=1.34"};
        BOOST_CHECK_NO_THROW(op.configure(cnf_opt));
        argument_type arg{{channel_1.begin(),channel_1.end()},
                          {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);
        
        string result = "-1.466e01 4.5e01\n"
                        "-1.416e01 1.3e01\n"
                        "-1.366e01 5.2e01\n"
                        "-1.316e01 5.1e01\n"
                        "-1.266e01 5.1e01\n" 
                        "-1.216e01 6.2e01\n" 
                        "-1.166e01 6.9e01\n"
                        "-1.116e01 8.300000000000001e01\n"
                        "-1.066e01 4.1e01\n"
                        "-1.016e01 4.1e01\n"
                        "-9.66e00 4.9e01\n"
                        "-9.16e00 5.8e01\n"
                        "-8.66e00 8.4e01\n"
                        "-8.16e00 3.6e01\n"
                        "-7.66e00 4.2e01\n"
                        "-7.16e00 0.0e00\n"
                        "-6.66e00 5.0e01\n"
                        "-6.16e00 2.5e01\n"
                        "-5.66e00 7.1e01\n"
                        "-5.16e00 6.8e01\n"
                        "-4.66e00 0.0e00\n"
                        "-4.16e00 8.0e00\n"
                        "-3.66e00 4.9e01\n"
                        "-3.16e00 3.4e01\n"
                        "-2.66e00 2.5e01\n"
                        "-2.16e00 5.6e01\n"
                        "-1.66e00 8.5e01\n"
                        "-1.16e00 8.0e01\n" 
                        "-6.6e-01 3.3e01\n"
                        "-1.599999999999999e-01 5.6e01\n"
                        "3.400000000000001e-01 3.0e00\n"
                        "8.4e-01 5.6e01\n"
                        "1.34e00 9.5e01\n"
                        "1.84e00 6.3e01\n"
                        "2.34e00 3.3e01\n"
                        "2.84e00 4.2e01\n"
                        "3.34e00 2.4e01\n"
                        "3.84e00 3.2e01\n"
                        "4.34e00 9.199999999999999e01\n"
                        "4.84e00 3.5e01\n"
                        "5.34e00 5.7e01\n"
                        "5.84e00 3.8e01\n"
                        "6.34e00 3.0e01\n"
                        "6.84e00 9.0e01\n"
                        "7.34e00 3.1e01\n"
                        "7.84e00 7.5e01\n"
                        "8.34e00 1.7e01\n"
                        "8.84e00 6.3e01\n";

        BOOST_CHECK(stream.is_equal(result));
    }

    //-----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_usermax)
    {
        scale op;
        args_vector cnf_opt{"--delta=0.5","--cvalue=1.34","--center=30"};
        BOOST_CHECK_NO_THROW(op.configure(cnf_opt));
        argument_type arg{{channel_1.begin(),channel_1.end()},
                          {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);

        string result = "-1.366e01 4.5e01\n"
                        "-1.316e01 1.3e01\n"
                        "-1.266e01 5.2e01\n"
                        "-1.216e01 5.1e01\n"
                        "-1.166e01 5.1e01\n" 
                        "-1.116e01 6.2e01\n" 
                        "-1.066e01 6.9e01\n"
                        "-1.016e01 8.300000000000001e01\n"
                        "-9.66e00 4.1e01\n"
                        "-9.16e00 4.1e01\n"
                        "-8.66e00 4.9e01\n"
                        "-8.16e00 5.8e01\n"
                        "-7.66e00 8.4e01\n"
                        "-7.16e00 3.6e01\n"
                        "-6.66e00 4.2e01\n"
                        "-6.16e00 0.0e00\n"
                        "-5.66e00 5.0e01\n"
                        "-5.16e00 2.5e01\n"
                        "-4.66e00 7.1e01\n"
                        "-4.16e00 6.8e01\n"
                        "-3.66e00 0.0e00\n"
                        "-3.16e00 8.0e00\n"
                        "-2.66e00 4.9e01\n"
                        "-2.16e00 3.4e01\n"
                        "-1.66e00 2.5e01\n"
                        "-1.16e00 5.6e01\n"
                        "-6.6e-01 8.5e01\n"
                        "-1.599999999999999e-01 8.0e01\n" 
                        "3.400000000000001e-01 3.3e01\n"
                        "8.4e-01 5.6e01\n"
                        "1.34e00 3.0e00\n"
                        "1.84e00 5.6e01\n"
                        "2.34e00 9.5e01\n"
                        "2.84e00 6.3e01\n"
                        "3.34e00 3.3e01\n"
                        "3.84e00 4.2e01\n"
                        "4.34e00 2.4e01\n"
                        "4.84e00 3.2e01\n"
                        "5.34e00 9.199999999999999e01\n"
                        "5.84e00 3.5e01\n"
                        "6.34e00 5.7e01\n"
                        "6.84e00 3.8e01\n"
                        "7.34e00 3.0e01\n"
                        "7.84e00 9.0e01\n"
                        "8.34e00 3.1e01\n"
                        "8.84e00 7.5e01\n"
                        "9.34e00 1.7e01\n"
                        "9.84e00 6.3e01\n";

        BOOST_CHECK(stream.is_equal(result));
    }


BOOST_AUTO_TEST_SUITE_END()



