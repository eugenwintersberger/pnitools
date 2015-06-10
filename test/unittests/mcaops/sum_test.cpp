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
//  Created on: Oct 7, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "operations_test_common.hpp"
#include <mcaops/operations/sum.hpp>

using namespace pni::core;
using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_SUITE(sum_operation_test)

BOOST_AUTO_TEST_CASE(test_sum_1)
{
    auto data = array_type::create(shape_t{4},
                storage_type{1., -5.39, 10.3948, 9.739 });
    auto channels = array_type::create(shape_t{4},
                storage_type{0,1,2,3});

    argument_type arg{{channels.begin(),channels.end()},
                      {data.begin(),data.end()}};

    sum o;
    o(arg);
    output_test_stream stream; 
    o.stream_result(stream);

    BOOST_CHECK( stream.is_equal("1.57438e01"));
}

BOOST_AUTO_TEST_SUITE_END()

