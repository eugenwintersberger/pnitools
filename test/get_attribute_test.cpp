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
 *  Created on: Jun 28, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "../src/common/is_field.hpp"
#include "../src/common/is_valid.hpp"
#include "../src/common/is_attribute.hpp"
#include "../src/common/set_unit.hpp"
#include "get_attribute_test.hpp"
#include "../src/common/get_name.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(get_attribute_test);

//-----------------------------------------------------------------------------
void get_attribute_test::setUp()
{
    file = h5::nxfile::create_file("is_valid.nx",true,0);
    group = file.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = file.create_field<uint32>("data");
    field.attr<string>("units").write("mm");
}

//-----------------------------------------------------------------------------
void get_attribute_test::tearDown() 
{ 
    field.close();
    group.close();
    file.close();
}


//-----------------------------------------------------------------------------
void get_attribute_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_types object = group;
    CPPUNIT_ASSERT(is_valid(get_attribute(object,"NX_class")));
    CPPUNIT_ASSERT(is_attribute(get_attribute(object,"NX_class")));
    CPPUNIT_ASSERT(get_name(get_attribute(object,"NX_class")) == "NX_class");

}

//-----------------------------------------------------------------------------
void get_attribute_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_types object = field;

    CPPUNIT_ASSERT(is_attribute(get_attribute(object,"units")));
    CPPUNIT_ASSERT(get_name(get_attribute(object,"units")) == "units");

}

//-----------------------------------------------------------------------------
void get_attribute_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(get_attribute(object_types(group.attr("NX_class")),"bla"),
                         nxattribute_error);
}

