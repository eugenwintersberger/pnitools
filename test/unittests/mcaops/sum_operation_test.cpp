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

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <vector>
#include <list>
#include <sstream>

#include "sum_operation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(sum_operation_test);

//-----------------------------------------------------------------------------
void sum_operation_test::setUp() 
{
    ref_data = {1., -5.39, 10.3948, 9.739 };
}
//-----------------------------------------------------------------------------
void sum_operation_test::tearDown() {}

//-----------------------------------------------------------------------------
void sum_operation_test::test_sum_static()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    sum_operation op;
    channels = array_type::create(shape_t{ref_data.size()});
    data     = array_type::create(shape_t{ref_data.size()});

    std::copy(ref_data.begin(),ref_data.end(),data.begin());

    op(channels,data);
    
    std::stringstream ss;
    ss<<op;
    double result = 0.0;
    ss>>result;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(result,15.7438,1.e-8);
}

