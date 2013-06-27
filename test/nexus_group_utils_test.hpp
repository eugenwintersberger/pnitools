/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
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
 *  Created on: Jun 27, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "../src/common/nexus_group_utils.hpp"
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;

using namespace pni::io::nx;

class nexus_group_utils_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(nexus_group_utils_test);
        CPPUNIT_TEST(test_find_by_class);
        CPPUNIT_TEST(test_find_by_name);
        CPPUNIT_TEST(test_find_by_all);
        CPPUNIT_TEST(test_get_no_create);
        CPPUNIT_TEST(test_get_create);
        CPPUNIT_TEST(test_create);
        CPPUNIT_TEST_SUITE_END();

        h5::nxfile file;
        h5::nxgroup rootg;
        h5::nxgroup g;
        
    public:
        void setUp();
        void tearDown();

        void test_find_by_name();
        void test_find_by_class();
        void test_find_by_all();
        void test_get_no_create();
        void test_get_create();
        void test_create();

};

