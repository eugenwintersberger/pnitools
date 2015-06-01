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
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test common components
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>

#include <common/string_utils.hpp>


BOOST_AUTO_TEST_SUITE(string_utilies_tests)

BOOST_AUTO_TEST_CASE(test_trim)
{
    BOOST_TEST_MESSAGE("common components test: trim");
    BOOST_CHECK(trim("   bla hello   world ")=="bla hello   world");
}

BOOST_AUTO_TEST_CASE(test_to_lower)
{
    BOOST_TEST_MESSAGE("common components test: to_lower");
    BOOST_CHECK(to_lower("HELLO WORLD")=="hello world");
}

BOOST_AUTO_TEST_CASE(test_to_upper)
{
    BOOST_TEST_MESSAGE("common components test: to_upper");
    BOOST_CHECK(to_upper("hello world")=="HELLO WORLD");
}

BOOST_AUTO_TEST_SUITE_END()




