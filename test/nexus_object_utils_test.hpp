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

#include "../src/common/nexus_object_utils.hpp"
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;

using namespace pni::io::nx;

//-----------------------------------------------------------------------------
class nexus_object_utils_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(nexus_object_utils_test);
        CPPUNIT_TEST(test_object_inquery);
        CPPUNIT_TEST(test_object_class);
        CPPUNIT_TEST(test_object_unit);
        CPPUNIT_TEST_SUITE_END();

        h5::nxfile file;
        
    public:
        void setUp();
        void tearDown();

        void test_object_inquery();
        void test_object_class();
        void test_object_unit();

        void test_object_bool();
};

