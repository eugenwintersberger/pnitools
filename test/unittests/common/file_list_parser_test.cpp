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
//  Created on: Jun 26, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <common/file_list_parser.hpp>

struct file_list_fixture
{
    typedef std::vector<string> list_type; 

    list_type name_list;
    list_type range_list;
    list_type mixed_list; 

    file_list_fixture():
        name_list(list_type{"../../data/fio/scan_mca_00001.fio",
                            "../../data/fio/scan_mca_00002.fio",
                            "../../data/fio/scan_mca_00003.fio",
                            "../../data/fio/scan_mca_00004.fio",
                            "../../data/fio/scan_mca_00005.fio",
                            "../../data/fio/scan_mca_00006.fio",
                            "../../data/fio/scan_mca_00007.fio",
                            "../../data/fio/scan_mca_00008.fio"}),
        range_list(list_type{"../../data/fio/scan_mca_%05i.fio:1:9"}),
        mixed_list(list_type{"../../data/fio/scan_mca_00001.fio",
                             "../../data/fio/scan_mca_00002.fio",
                             "../../data/fio/scan_mca_%05i.fio:3:8",
                             "../../data/fio/scan_mca_00008.fio"})
    {}

};


BOOST_FIXTURE_TEST_SUITE(file_list_parser_tests,file_list_fixture)

typedef std::list<file> result_t;
//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_parse_list)
{
    result_t result_list;
    BOOST_REQUIRE_NO_THROW(result_list =
            file_list_parser::parse<result_t>(name_list));
    BOOST_CHECK_EQUAL(result_list.size(),name_list.size());

    auto niter = name_list.begin();
    auto riter = result_list.begin();
    for(;riter != result_list.end(); ++riter,++niter)
    {
        BOOST_CHECK_EQUAL(riter->path() , *niter);
    }
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_parse_range)
{
    result_t result_list;
    BOOST_REQUIRE_NO_THROW(result_list = 
                           file_list_parser::parse<result_t>(range_list));

    BOOST_CHECK_EQUAL(result_list.size() , name_list.size());
    auto niter = name_list.begin();
    auto riter = result_list.begin();
    for(;riter != result_list.end(); ++riter,++niter)
    {
       BOOST_CHECK_EQUAL(riter->path() , *niter); 
    }
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_parse_mixed)
{
    result_t result_list;
    BOOST_REQUIRE_NO_THROW(result_list = 
                           file_list_parser::parse<result_t>(mixed_list));

    BOOST_CHECK_EQUAL(result_list.size() , name_list.size());
    auto niter = name_list.begin();
    auto riter = result_list.begin();
    for(;riter != result_list.end();++riter,++niter)
    {
       BOOST_CHECK_EQUAL(riter->path() , *niter); 
    }
}

BOOST_AUTO_TEST_SUITE_END()
