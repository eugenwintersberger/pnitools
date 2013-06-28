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

    CPPUNIT_ASSERT(is_valid(find_group_by_name(rootg,"group")));
    CPPUNIT_ASSERT(!is_valid(find_group_by_name(rootg,"bla")));
}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_find_by_class()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(is_valid(find_group_by_class(rootg,"NXentry")));
    CPPUNIT_ASSERT(!is_valid(find_group_by_class(rootg,"NXinstrument")));
}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_find_by_all()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(is_valid(find_group_by_name_and_class(rootg,"group","NXentry")));
    CPPUNIT_ASSERT(!is_valid(find_group_by_name_and_class(rootg,"hallo","NXentry")));
    CPPUNIT_ASSERT(!is_valid(find_group_by_name_and_class(rootg,"group","NXinstrument")));

}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxgroup tg;

    CPPUNIT_ASSERT_NO_THROW(tg = create_group(rootg,"entry2","NXentry"));
    CPPUNIT_ASSERT(is_group(tg));
    CPPUNIT_ASSERT_THROW(create_group(rootg,"entry2"),nxgroup_error);
    CPPUNIT_ASSERT_NO_THROW(create_group(rootg,"entry3"));
    CPPUNIT_ASSERT(is_valid(tg = create_group(rootg,"entry4","NXentry")));
    CPPUNIT_ASSERT(is_valid(tg));

    //here we test the case that we use a parent class that differs in type from
    //the group type 
    CPPUNIT_ASSERT(is_valid(tg = create_group(rootg,"log","NXlog")));
    CPPUNIT_ASSERT(is_class(tg,"NXlog"));
    CPPUNIT_ASSERT(is_group(tg));
    
}

//-----------------------------------------------------------------------------
void nexus_group_utils_test::test_get_no_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g;
    g=create_group(rootg,"entry","NXentry");
    g=create_group(g,"instrument","NXinstrument");
    g=create_group(g,"detector","NXdetector");

    CPPUNIT_ASSERT_THROW(get_group(rootg,"entry10","NXentry",false),nxgroup_error);
    CPPUNIT_ASSERT(is_valid(g=get_group(rootg,"entry","NXentry",false)));

    nxpath p = path_from_string("../:NXentry/:NXinstrument/:NXdetector");
    CPPUNIT_ASSERT(is_valid(get_group(g,p,false)));
    CPPUNIT_ASSERT(is_valid(g =get_group(g,path_from_string("././:NXinstrument/:NXdetector"),
                    false)));
    CPPUNIT_ASSERT(is_class(g,"NXdetector"));
}

//------------------------------------------------------------------------------
void nexus_group_utils_test::test_get_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxgroup g;

    CPPUNIT_ASSERT(is_valid(g=get_group(rootg,"entry","NXentry")));
    CPPUNIT_ASSERT(is_valid(g=get_group(rootg,
                    path_from_string("./entry2:NXentry/instrument:NXinstrument/"))));
    CPPUNIT_ASSERT(is_valid(g=get_group(rootg,
                    path_from_string("./entry2/:NXinstrument/log"))));
    CPPUNIT_ASSERT(is_valid(g=get_group(rootg,
                    path_from_string("./entry2/:NXinstrument/detector:NXdetector"))));

    //should throw an error as the group does not exist and cannot be created
    //due to a missing name
    CPPUNIT_ASSERT_THROW(get_group(rootg,
                path_from_string("./entry2/:NXsource/")),nxgroup_error);
    
    CPPUNIT_ASSERT_THROW(get_group(rootg,
                path_from_string("./entry2/instrument/:NXsource/data")),nxgroup_error);

}
