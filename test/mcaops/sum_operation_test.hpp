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
 *  Created on: Oct 7, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <iostream>
#include <memory>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "mcaops/sum_operation.hpp"
#include "../compare.hpp"
#include "../type_id.hpp"

#ifdef NODEBUG
#include <boost/foreach.hpp>
#endif

using namespace pni::core;

//-----------------------------------------------------------------------------
class sum_operation_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(sum_operation_test);
        CPPUNIT_TEST(test_sum_static);
        CPPUNIT_TEST_SUITE_END();

        typedef operation::array_type array_type;
        array_type channels;
        array_type data;
        std::vector<array_type::value_type> ref_data ;
    public:
        void setUp();
        void tearDown();

        void test_sum_static();
};

