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
#include <iostream>
#include <memory>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "common/column.hpp"
#include "../compare.hpp"
#include "../type_id.hpp"
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/scalar.hpp>
#include <pni/core/array.hpp>

#ifdef NODEBUG
#include <boost/foreach.hpp>
#endif

using namespace pni::core;
//---------------------------------------------------------------------
template<typename IT,typename T>
void init_cell(const shape_t &s, IT init_value, scalar<T> &cell)
{
    cell = T(init_value); 
}
/*
    typename = typename std::enable_if<
    !std::is_same<CT,scalar<typename CT::value_type> >::value 
    >::type
    */
//---------------------------------------------------------------------
template<typename T,typename CT >
void init_cell(const shape_t &s,
               T init_value, 
               CT &cell)
{
    typedef typename CT::value_type value_type;
    cell = CT(s);
    std::fill(cell.begin(),cell.end(),value_type(init_value));
}

//---------------------------------------------------------------------
template<typename T>
void init_cell(const shape_t &s,T init_value,array &cell)
{
    typedef darray<T> array_t;

    array_t a(s);
    std::fill(a.begin(),a.end(),init_value);
    cell = array(a);
}

//-----------------------------------------------------------------------------
template<typename STYPE>
class column_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(column_test<STYPE>);
        CPPUNIT_TEST(test_creation);
        CPPUNIT_TEST(test_move_creation);
        CPPUNIT_TEST(test_copy_creation);
/*        CPPUNIT_TEST(test_copy_assignment);
        CPPUNIT_TEST(test_move_assignment);*/
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST_SUITE_END();

        //the cell type
        typedef typename STYPE::value_type cell_t;
        //the column type
        typedef column<STYPE> column_t;

        shape_t cell_shape;
        std::vector<cell_t> ref_list;
        
    public:
        void setUp();
        void tearDown();

        void test_creation();
        void test_move_creation();
        void test_copy_creation();
        void test_inquery();
        void test_access();
};

//-----------------------------------------------------------------------------
template<typename STYPE> void column_test<STYPE>::setUp() 
{ 
    cell_shape = shape_t({4,10});
    
    for(size_t i=0;i<10;i++)
    {
        cell_t s;
        init_cell(cell_shape,i,s);
        ref_list.push_back(s);
    }
}

//-----------------------------------------------------------------------------
template<typename STYPE> void column_test<STYPE>::tearDown() { }


//-----------------------------------------------------------------------------
template<typename STYPE> 
void column_test<STYPE>::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //construction from constructor
    column_t col1;
    CPPUNIT_ASSERT(col1.name() == "");
    CPPUNIT_ASSERT(col1.unit() == "");
    CPPUNIT_ASSERT(col1.size() == 0);

    //try creation from the helper functions
    auto col2 = create_column<STYPE>("hello","nm");
    CPPUNIT_ASSERT(col2.name() == "hello");
    CPPUNIT_ASSERT(col2.unit() == "nm");
    CPPUNIT_ASSERT(col2.size() == 0);

    //create with initial data
    auto col3 = create_column<STYPE>("hello2","m",ref_list);
    CPPUNIT_ASSERT(col3.name() == "hello2");
    CPPUNIT_ASSERT(col3.unit() == "m");
    CPPUNIT_ASSERT(col3.size() == ref_list.size());

}

//-----------------------------------------------------------------------------
template<typename STYPE> 
void column_test<STYPE>::test_copy_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //construction from constructor
    auto c1 = create_column<STYPE>("hello","m",ref_list);
    column_t c2(c1);
    CPPUNIT_ASSERT(c2.name() == c1.name());
    CPPUNIT_ASSERT(c2.unit() == c1.unit());
    CPPUNIT_ASSERT(c2.size() == c1.size());

}

//-----------------------------------------------------------------------------
template<typename STYPE> 
void column_test<STYPE>::test_move_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //construction from constructor
    auto c1 = create_column<STYPE>("hello","m",ref_list);
    column_t c2 = std::move(c1);
    CPPUNIT_ASSERT(c2.name() == "hello");
    CPPUNIT_ASSERT(c2.unit() == "m");
    CPPUNIT_ASSERT(c2.size() == ref_list.size());
    CPPUNIT_ASSERT(c1.name() == "");
    CPPUNIT_ASSERT(c1.unit() == "");
    CPPUNIT_ASSERT(c1.size() == 0);

}
//-----------------------------------------------------------------------------
template<typename STYPE> 
void column_test<STYPE>::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    auto c1 = create_column<STYPE>("hello","m",ref_list);
    CPPUNIT_ASSERT(c1.type_id() == type_id(*(ref_list.begin())));
    CPPUNIT_ASSERT(c1.size() == ref_list.size());
    CPPUNIT_ASSERT(c1.name() == "hello");
    CPPUNIT_ASSERT(c1.unit() == "m");
}

//-----------------------------------------------------------------------------
template<typename STYPE>
void column_test<STYPE>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto c1 = create_column<STYPE>("hello","m",ref_list);
    size_t i=0;

    auto riter = ref_list.begin();
    auto citer = c1.begin();
    for(; citer != c1.end(); ++riter,++citer)
    {
        auto iter1 = riter->begin();
        auto iter2 = citer->begin();
        for(;iter1!=riter->end();++iter1,++iter2) compare(*iter1,*iter2);
    }
}
