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

#include "nexus_group_utils_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(nexus_group_utils_test);

//-----------------------------------------------------------------------------
void nexus_group_utils_test::setUp()
{
    file = h5::nxfile::create_file("groups.nx",true,0);
    file.create_group("group","NXentry");
    file.create_field<uint32>("data");
    rootg = file["/"];
}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::tearDown() 
{ 
    rootg.close();
    g.close();
    file.close();
}


//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_find_by_name()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(find_group_by_name(rootg,"group",g));
    CPPUNIT_ASSERT(!find_group_by_name(rootg,"bla",g));
}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_find_by_class()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(find_group_by_class(rootg,"NXentry",g));
    CPPUNIT_ASSERT(!find_group_by_class(rootg,"NXinstrument",g));
}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_find_by_all()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(find_group_by_name_and_class(rootg,"group","NXentry",g));
    CPPUNIT_ASSERT(!find_group_by_name_and_class(rootg,"hallo","NXentry",g));
    CPPUNIT_ASSERT(!find_group_by_name_and_class(rootg,"group","NXinstrument",g));

}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_get_no_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
}

//------------------------------------------------------------------------------
void nexus_group_utils_test::test_get_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}
