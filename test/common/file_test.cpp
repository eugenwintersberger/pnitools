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

#include "file_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(file_test);

//-----------------------------------------------------------------------------
void file_test::setUp()
{
    p1 = "./data/fio/scan_mca_00001.fio";
    p2 = ".";
    p3 = "./nothing.txt";
}

//-----------------------------------------------------------------------------
void file_test::tearDown() { }


//-----------------------------------------------------------------------------
void file_test::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    file f;
    //should be ok - the file exists
    CPPUNIT_ASSERT_NO_THROW(f = file(p1));
    //not ok - we try to open a directory
    CPPUNIT_ASSERT_THROW(f = file(p3),file_error);;
    //not ok - the file does not exist
    CPPUNIT_ASSERT_THROW(f = file(p2),file_error);
}

//-----------------------------------------------------------------------------
void file_test::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    file f(p1);
    CPPUNIT_ASSERT(f.name() == "scan_mca_00001.fio");
    CPPUNIT_ASSERT(f.extension() == ".fio");
    CPPUNIT_ASSERT(f.path() == "./data/fio/scan_mca_00001.fio");
    CPPUNIT_ASSERT(f.base() == "./data/fio");
}
