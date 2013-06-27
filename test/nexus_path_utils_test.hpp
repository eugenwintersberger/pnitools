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

#include "../src/common/nexus_path_utils.hpp"
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class nexus_path_utils_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(nexus_path_utils_test);
        CPPUNIT_TEST(test_path_input);
        CPPUNIT_TEST(test_path_strrep);
        CPPUNIT_TEST(test_path_output);
        CPPUNIT_TEST(test_path_comparison);
        CPPUNIT_TEST(test_path_split);
        CPPUNIT_TEST_SUITE_END();

        string p1;
        string p2;
        string p3;

    public:
        void setUp();
        void tearDown();

        void test_path_strrep();
        void test_path_input();
        void test_path_output();
        void test_path_comparison();
        void test_path_split();

};

