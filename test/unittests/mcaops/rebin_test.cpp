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


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rebin_no_x_no_norm)
    {
        rebin op;
        BOOST_CHECK_NO_THROW(op.configure(args_vector{"-b10","--noxrebin"}));
        auto arg = argument_type{{channels.begin(),channels.end()},
                                 {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);

        string result= "0.0e00 5.08e02\n"
                       "1.0e00 4.83e02\n"
                       "2.0e00 4.26e02\n"
                       "3.0e00 4.75e02\n"
                       "4.0e00 4.01e02\n";

        BOOST_CHECK(stream.is_equal(result));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rebin_no_x_norm)
    {
        rebin op;
        auto cnf_opts = args_vector{"-b10","--normalize","--noxrebin"};
        BOOST_CHECK_NO_THROW(op.configure(cnf_opts));
        auto arg = argument_type{{channels.begin(),channels.end()},
                                 {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);

        string result= "0.0e00 5.08e01\n"
                       "1.0e00 4.83e01\n"
                       "2.0e00 4.26e01\n"
                       "3.0e00 4.75e01\n"
                       "4.0e00 5.0125e01\n";

        BOOST_CHECK(stream.is_equal(result));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_rebin_x_norm)
    {
        rebin op;
        args_vector cnf_opts{"-b10","--normalize"};
        BOOST_CHECK_NO_THROW(op.configure(cnf_opts));
        argument_type arg{{channels.begin(),channels.end()},
                          {mca.begin(),mca.end()}};
        BOOST_CHECK_NO_THROW(op(arg));
        op.stream_result(stream);
        
        string result= "4.5e00 5.08e01\n"
                       "1.45e01 4.83e01\n"
                       "2.45e01 4.26e01\n"
                       "3.45e01 4.75e01\n"
                       "4.35e01 5.0125e01\n";
        
        BOOST_CHECK(stream.is_equal(result));
    }

BOOST_AUTO_TEST_SUITE_END()



