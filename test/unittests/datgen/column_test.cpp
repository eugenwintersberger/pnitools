//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
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
//  Created on: Sep 12, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <vector>
#include <list>
#include <boost/mpl/list.hpp>
#include "cell_init.hpp"
#include <common/column.hpp>


typedef std::vector<scalar<double>>        vector_scalar_cell_t;
typedef std::vector<dynamic_array<double>> vector_array_cell_t;
typedef std::vector<array>                 vector_te_array_cell_t;
typedef std::list<scalar<double>>          list_scalar_cell_t;
typedef std::list<dynamic_array<double>>   list_array_cell_t;
typedef std::list<array>                   list_te_array_cell_t;

typedef boost::mpl::list<vector_scalar_cell_t,
                         vector_array_cell_t,
                         vector_te_array_cell_t,
                         list_scalar_cell_t,
                         list_array_cell_t,
                         list_te_array_cell_t> test_types;

template<typename S> struct column_trait
{
    typedef typename S::value_type value_type;
    typedef column<S> column_type;
    typedef std::vector<value_type> ref_type;
};

template<typename A> shape_t init_shape(const A &a)
{
    return shape_t({3,4});
}

template<typename T> shape_t init_shape(const scalar<T> &a)
{
    return shape_t();
}

//-----------------------------------------------------------------------------
template<typename STYPE>
typename column_trait<STYPE>::ref_type create_reference() 
{ 
    typedef column_trait<STYPE> trait_type;
    typedef typename trait_type::value_type cell_type;
    typedef typename trait_type::ref_type ref_type;

    shape_t cell_shape = init_shape(cell_type());
    ref_type ref_list;
    
    for(size_t i=0;i<10;i++)
    {
        cell_type s;
        init_cell(cell_shape,i,s);
        ref_list.push_back(s);
    }

    return ref_list;
}



BOOST_AUTO_TEST_SUITE(column_test)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_creation,STYPE,test_types)
{
    typedef column_trait<STYPE> trait_type;
    typedef typename trait_type::column_type column_type;
    typedef typename trait_type::ref_type ref_type;

    //construction from constructor
    column_type col1;
    BOOST_CHECK_EQUAL(col1.name(),"");
    BOOST_CHECK_EQUAL(col1.unit(),"");
    BOOST_CHECK_EQUAL(col1.size(),0);

    //try creation from the helper functions
    auto col2 = create_column<STYPE>("hello","nm");
    BOOST_CHECK_EQUAL(col2.name(),"hello");
    BOOST_CHECK_EQUAL(col2.unit(),"nm");
    BOOST_CHECK_EQUAL(col2.size(),0);

    //create with initial data
    ref_type ref_list = create_reference<STYPE>();
    auto col3 = create_column<STYPE>("hello2","m",ref_list);
    BOOST_CHECK_EQUAL(col3.name(),"hello2");
    BOOST_CHECK_EQUAL(col3.unit(),"m");
    BOOST_CHECK_EQUAL(col3.size(),ref_list.size());

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_creation,STYPE,test_types)
{
    typedef column_trait<STYPE> trait_type;
    typedef typename trait_type::ref_type ref_type;
    typedef typename trait_type::column_type column_type;

    //construction from constructor
    ref_type ref_list = create_reference<STYPE>();
    auto c1 = create_column<STYPE>("hello","m",ref_list);
    column_type c2(c1);

    BOOST_CHECK_EQUAL(c2.name(),c1.name());
    BOOST_CHECK_EQUAL(c2.unit(),c1.unit());
    BOOST_CHECK_EQUAL(c2.size(),c1.size());
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_creation,STYPE,test_types)
{
    typedef column_trait<STYPE> trait_type;
    typedef typename trait_type::ref_type ref_type;
    typedef typename trait_type::column_type column_type;

    //construction from constructor
    ref_type ref_list = create_reference<STYPE>();
    auto c1 = create_column<STYPE>("hello","m",ref_list);
    column_type c2(std::move(c1));

    BOOST_CHECK_EQUAL(c2.name(),"hello");
    BOOST_CHECK_EQUAL(c2.unit(),"m");
    BOOST_CHECK_EQUAL(c2.size(),ref_list.size());
    BOOST_CHECK_EQUAL(c1.name(),"");
    BOOST_CHECK_EQUAL(c1.unit(),"");
    BOOST_CHECK_EQUAL(c1.size(),0);

}
//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_inquery,STYPE,test_types)
{
    typedef column_trait<STYPE> trait_type;
    typedef typename trait_type::ref_type ref_type;

    ref_type ref_list = create_reference<STYPE>();
    auto c1 = create_column<STYPE>("hello","m",ref_list);

    BOOST_CHECK_EQUAL(c1.type_id(),type_id(*(ref_list.begin())));
    BOOST_CHECK_EQUAL(c1.size(),ref_list.size());
    BOOST_CHECK_EQUAL(c1.name(),"hello");
    BOOST_CHECK_EQUAL(c1.unit(),"m");
    //BOOST_CHECK_EQUAL(c1.rank(),0;
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_access,STYPE,test_types)
{
    typedef column_trait<STYPE> trait_type;

    typename trait_type::ref_type ref_list(10);
    auto c1 = create_column<STYPE>("hello","m",ref_list);
    size_t i=0;

    auto riter = ref_list.begin();
    auto citer = c1.begin();
    for(; citer != c1.end(); ++riter,++citer)
    {
        //iterate over the cell
        auto iter1 = riter->begin();
        auto iter2 = citer->begin();
        //CPPUNIT_ASSERT(*iter1==*iter2);
    }
}

BOOST_AUTO_TEST_SUITE_END()
