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
 *  Created on: Jun 26, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "../src/common/file_list_parser.hpp"
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

using namespace pni::core;

//-----------------------------------------------------------------------------
class file_list_parser_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(file_list_parser_test);
        CPPUNIT_TEST(test_parse_list);
        CPPUNIT_TEST(test_parse_range);
        CPPUNIT_TEST(test_parse_mixed);
        CPPUNIT_TEST_SUITE_END();
        
        std::vector<string> name_list;
        std::vector<string> range_list;
        std::vector<string> mixed_list;

        typedef std::list<file> result_t;

        result_t result_list;
    public:
        void setUp();
        void tearDown();

        void test_parse_list();
        void test_parse_range();
        void test_parse_mixed();
};

