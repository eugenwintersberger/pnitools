//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
//  Created on: Oct 7, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "string_utils_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(string_utils_test);

//-----------------------------------------------------------------------------
void string_utils_test::setUp()
{
    p1 = "./data/fio/scan_mca_00001.fio";
    p2 = ".";
    p3 = "./nothing.txt";
}

//-----------------------------------------------------------------------------
void string_utils_test::tearDown() { }


//-----------------------------------------------------------------------------
void string_utils_test::test_trim()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(trim("   bla hello   world ")=="bla hello   world");
}

//-----------------------------------------------------------------------------
void string_utils_test::test_to_lower()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(to_lower("HELLO WORLD")=="hello world");
}

//----------------------------------------------------------------------------
void string_utils_test::test_to_upper()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(to_upper("hello world")=="HELLO WORLD");
}
