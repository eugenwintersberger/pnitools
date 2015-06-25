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
//************************************************************************
//
//  Created on: Jun 26, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <common/file.hpp>

using namespace pni::core;

struct file_fixture
{
    string _p1;
    string _p2;
    string _p3;

    file_fixture():
        _p1("../../data/fio/scan_mca_00001.fio"),
        _p2("."),
        _p3("./nothing.txt")
    {}
};

BOOST_FIXTURE_TEST_SUITE(file_tests,file_fixture)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_default_construction)
{
    file f;
    BOOST_CHECK_EQUAL(f.name(),"");
    BOOST_CHECK_EQUAL(f.extension(),"");
    BOOST_CHECK_EQUAL(f.path(),"");
    BOOST_CHECK_EQUAL(f.base(),"");
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_creation)
{
    //should be ok - the file exists
    BOOST_CHECK_NO_THROW(file f(_p1));
    //not ok - we try to open a directory
    BOOST_CHECK_THROW(file f(_p2),file_error);;
    //not ok - the file does not exist
    BOOST_CHECK_THROW(file f(_p3),file_error);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_inquery)
{
    file f(_p1);
    BOOST_CHECK_EQUAL(f.name() , "scan_mca_00001.fio");
    BOOST_CHECK_EQUAL(f.extension() , ".fio");
    BOOST_CHECK_EQUAL(f.path() , "../../data/fio/scan_mca_00001.fio");
    BOOST_CHECK_EQUAL(f.base() , "../../data/fio");
}

BOOST_AUTO_TEST_SUITE_END()
