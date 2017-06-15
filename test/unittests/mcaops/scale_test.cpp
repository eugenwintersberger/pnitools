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

        string result = "-1.466000e+01 +4.500000e+01\n"
                        "-1.416000e+01 +1.300000e+01\n"
                        "-1.366000e+01 +5.200000e+01\n"
                        "-1.316000e+01 +5.100000e+01\n"
                        "-1.266000e+01 +5.100000e+01\n"
                        "-1.216000e+01 +6.200000e+01\n"
                        "-1.166000e+01 +6.900000e+01\n"
                        "-1.116000e+01 +8.300000e+01\n"
                        "-1.066000e+01 +4.100000e+01\n"
                        "-1.016000e+01 +4.100000e+01\n"
                        "-9.660000e+00 +4.900000e+01\n"
                        "-9.160000e+00 +5.800000e+01\n"
                        "-8.660000e+00 +8.400000e+01\n"
                        "-8.160000e+00 +3.600000e+01\n"
                        "-7.660000e+00 +4.200000e+01\n"
                        "-7.160000e+00 +0.000000e+00\n"
                        "-6.660000e+00 +5.000000e+01\n"
                        "-6.160000e+00 +2.500000e+01\n"
                        "-5.660000e+00 +7.100000e+01\n"
                        "-5.160000e+00 +6.800000e+01\n"
                        "-4.660000e+00 +0.000000e+00\n"
                        "-4.160000e+00 +8.000000e+00\n"
                        "-3.660000e+00 +4.900000e+01\n"
                        "-3.160000e+00 +3.400000e+01\n"
                        "-2.660000e+00 +2.500000e+01\n"
                        "-2.160000e+00 +5.600000e+01\n"
                        "-1.660000e+00 +8.500000e+01\n"
                        "-1.160000e+00 +8.000000e+01\n"
                        "-6.600000e-01 +3.300000e+01\n"
                        "-1.600000e-01 +5.600000e+01\n"
                        "+3.400000e-01 +3.000000e+00\n"
                        "+8.400000e-01 +5.600000e+01\n"
                        "+1.340000e+00 +9.500000e+01\n"
                        "+1.840000e+00 +6.300000e+01\n"
                        "+2.340000e+00 +3.300000e+01\n"
                        "+2.840000e+00 +4.200000e+01\n"
                        "+3.340000e+00 +2.400000e+01\n"
                        "+3.840000e+00 +3.200000e+01\n"
                        "+4.340000e+00 +9.200000e+01\n"
                        "+4.840000e+00 +3.500000e+01\n"
                        "+5.340000e+00 +5.700000e+01\n"
                        "+5.840000e+00 +3.800000e+01\n"
                        "+6.340000e+00 +3.000000e+01\n"
                        "+6.840000e+00 +9.000000e+01\n"
                        "+7.340000e+00 +3.100000e+01\n"
                        "+7.840000e+00 +7.500000e+01\n"
                        "+8.340000e+00 +1.700000e+01\n"
                        "+8.840000e+00 +6.300000e+01\n";

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

        string result = "-1.366000e+01 +4.500000e+01\n"
                        "-1.316000e+01 +1.300000e+01\n"
                        "-1.266000e+01 +5.200000e+01\n"
                        "-1.216000e+01 +5.100000e+01\n"
                        "-1.166000e+01 +5.100000e+01\n"
                        "-1.116000e+01 +6.200000e+01\n"
                        "-1.066000e+01 +6.900000e+01\n"
                        "-1.016000e+01 +8.300000e+01\n"
                        "-9.660000e+00 +4.100000e+01\n"
                        "-9.160000e+00 +4.100000e+01\n"
                        "-8.660000e+00 +4.900000e+01\n"
                        "-8.160000e+00 +5.800000e+01\n"
                        "-7.660000e+00 +8.400000e+01\n"
                        "-7.160000e+00 +3.600000e+01\n"
                        "-6.660000e+00 +4.200000e+01\n"
                        "-6.160000e+00 +0.000000e+00\n"
                        "-5.660000e+00 +5.000000e+01\n"
                        "-5.160000e+00 +2.500000e+01\n"
                        "-4.660000e+00 +7.100000e+01\n"
                        "-4.160000e+00 +6.800000e+01\n"
                        "-3.660000e+00 +0.000000e+00\n"
                        "-3.160000e+00 +8.000000e+00\n"
                        "-2.660000e+00 +4.900000e+01\n"
                        "-2.160000e+00 +3.400000e+01\n"
                        "-1.660000e+00 +2.500000e+01\n"
                        "-1.160000e+00 +5.600000e+01\n"
                        "-6.600000e-01 +8.500000e+01\n"
                        "-1.600000e-01 +8.000000e+01\n"
                        "+3.400000e-01 +3.300000e+01\n"
                        "+8.400000e-01 +5.600000e+01\n"
                        "+1.340000e+00 +3.000000e+00\n"
                        "+1.840000e+00 +5.600000e+01\n"
                        "+2.340000e+00 +9.500000e+01\n"
                        "+2.840000e+00 +6.300000e+01\n"
                        "+3.340000e+00 +3.300000e+01\n"
                        "+3.840000e+00 +4.200000e+01\n"
                        "+4.340000e+00 +2.400000e+01\n"
                        "+4.840000e+00 +3.200000e+01\n"
                        "+5.340000e+00 +9.200000e+01\n"
                        "+5.840000e+00 +3.500000e+01\n"
                        "+6.340000e+00 +5.700000e+01\n"
                        "+6.840000e+00 +3.800000e+01\n"
                        "+7.340000e+00 +3.000000e+01\n"
                        "+7.840000e+00 +9.000000e+01\n"
                        "+8.340000e+00 +3.100000e+01\n"
                        "+8.840000e+00 +7.500000e+01\n"
                        "+9.340000e+00 +1.700000e+01\n"
                        "+9.840000e+00 +6.300000e+01\n";

        BOOST_CHECK(stream.is_equal(result));
    }


BOOST_AUTO_TEST_SUITE_END()
