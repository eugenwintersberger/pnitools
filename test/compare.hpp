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
 *  Created on: Sep 12, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <type_traits>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/array.hpp>
#include <pni/core/id_type_map.hpp>

using namespace pni::core;

/*!
\brief compare integers and strings

This template function compares two values which are integers and strings. 
*/
template<typename T> 
void compare(T a,T b,
             typename std::enable_if<!std::is_floating_point<T>::value,T>::type* =0)
{
    CPPUNIT_ASSERT(a==b);
}


/*!
\brief compare floats

This function compares floating points values.
*/
template<typename T > 
void compare(T a,T b,
        typename std::enable_if<std::is_floating_point<T>::value,T>::type* =0)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-12);
}

/*!
\brief comparison of value_ref instances
*/
#define COMPARE_VALUE_REF(a,b,tid)\
    if((a.type_id() == tid) &&\
       (b.type_id() == tid)) \
    {\
        compare(a.as<id_type_map<tid>::type>(),\
                b.as<id_type_map<tid>::type>());\
        return; \
    }

void compare(const value_ref &a,const value_ref &b)
{
    COMPARE_VALUE_REF(a,b,type_id_t::UINT8);
    COMPARE_VALUE_REF(a,b,type_id_t::INT8);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT16);
    COMPARE_VALUE_REF(a,b,type_id_t::INT16);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT32);
    COMPARE_VALUE_REF(a,b,type_id_t::INT32);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT64);
    COMPARE_VALUE_REF(a,b,type_id_t::INT64);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT32);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT64);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT128);
    COMPARE_VALUE_REF(a,b,type_id_t::STRING);
}
