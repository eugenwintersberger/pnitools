//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//  Created on: Oct 8, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <iostream>
#include <memory>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "mcaops/scale_operation.hpp"
#include "../compare.hpp"

using namespace pni::core;

//-----------------------------------------------------------------------------
class scale_operation_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(scale_operation_test);
        CPPUNIT_TEST(test_configuration);
        CPPUNIT_TEST(test_exceptions);
        CPPUNIT_TEST(test_automax);
        CPPUNIT_TEST(test_usermax);
        CPPUNIT_TEST_SUITE_END();

        typedef operation::array_type array_type;
        typedef array_type::value_type value_type;
        array_type channels_1;
        array_type channels_2;
        array_type data;
        static const size_t nchannels = 48;
        shape_t shape;

        float64 compute_axis(float64 cv,size_t i,float64 d,size_t cb);

        void get_result(operation &o,array_type &axis);
    public:
        void setUp();
        void tearDown();

        void test_configuration();
        void test_exceptions();
        void test_automax();

        void test_usermax();
};

