/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jun 26, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "nexus_object_utils_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(nexus_object_utils_test);

//-----------------------------------------------------------------------------
void nexus_object_utils_test::setUp()
{
    file = h5::nxfile::create_file("test.nx",true,0);
    file.create_group("group","NXentry");
    file.create_field<uint32>("data");
}

//-----------------------------------------------------------------------------
void nexus_object_utils_test::tearDown() 
{ 
    file.close();
}


//-----------------------------------------------------------------------------
void nexus_object_utils_test::test_object_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_group(file["/group"]));
    CPPUNIT_ASSERT(!is_group(file["/data"]));

    CPPUNIT_ASSERT(is_field(file["/data"]));
    CPPUNIT_ASSERT(!is_group(file["/data"]));

}

//-----------------------------------------------------------------------------
void nexus_object_utils_test::test_object_class()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_class(file["/group"],"NXentry"));
    file.create_group("group2");
    CPPUNIT_ASSERT(!is_class(file["/group2"],"NXentry"));
    CPPUNIT_ASSERT_NO_THROW(set_class(file["/group2"],"NXentry"));
    CPPUNIT_ASSERT(is_class(file["/group2"],"NXentry"));

    CPPUNIT_ASSERT(get_class(file["/group"])=="NXentry"); 
}

//-----------------------------------------------------------------------------
void nexus_object_utils_test::test_object_unit()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(get_unit(file["/data"])!="m");
    CPPUNIT_ASSERT_NO_THROW(set_unit(file["/data"],"m"));
    CPPUNIT_ASSERT(get_unit(file["/data"])=="m");

    CPPUNIT_ASSERT_NO_THROW(set_unit(file["/data"],"mm"));
    CPPUNIT_ASSERT(get_unit(file["/data"])=="mm");

}
