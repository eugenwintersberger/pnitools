//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jun 25, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <common/file_queue.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

struct file_queue_fixture
{
    typedef std::vector<string> list_type;

    list_type name_list;
    list_type range_list;
    list_type mixed_list;

    file_queue_fixture():
        name_list(list_type{fs::path("../../data/fio/scan_mca_00001.fio").string(),
                            fs::path("../../data/fio/scan_mca_00002.fio").string(),
                            fs::path("../../data/fio/scan_mca_00003.fio").string(),
                            fs::path("../../data/fio/scan_mca_00004.fio").string(),
                            fs::path("../../data/fio/scan_mca_00005.fio").string(),
                            fs::path("../../data/fio/scan_mca_00006.fio").string(),
                            fs::path("../../data/fio/scan_mca_00007.fio").string(),
                            fs::path("../../data/fio/scan_mca_00008.fio").string()}),
        range_list(list_type{fs::path("../../data/fio/scan_mca_%05i.fio:1:9").string()}),
        mixed_list(list_type{fs::path("../../data/fio/scan_mca_00001.fio").string(),
                             fs::path("../../data/fio/scan_mca_00002.fio").string(),
                             fs::path("../../data/fio/scan_mca_%05i.fio:3:8").string(),
                             fs::path("../../data/fio/scan_mca_00008.fio").string()})
    {}

};


BOOST_FIXTURE_TEST_SUITE(file_queue_tests,file_queue_fixture)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_name_list)
{
    file_queue q;
    BOOST_REQUIRE_NO_THROW(q = fill_file_queue(name_list));
    BOOST_CHECK_EQUAL(q.size(),name_list.size());

    auto niter = name_list.begin();
    while(!q.empty())
    {
        BOOST_CHECK_EQUAL(q.front().path(),*niter++);
        q.pop();
    }
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_name_range)
{
    file_queue q;
    BOOST_REQUIRE_NO_THROW(q = fill_file_queue(range_list));
    BOOST_CHECK_EQUAL(q.size() , name_list.size());

    auto niter = name_list.begin();
    while(!q.empty())
    {
        BOOST_CHECK_EQUAL(q.front().path(),*niter++);
        q.pop();
    }
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_mixed)
{
    file_queue q;
    BOOST_REQUIRE_NO_THROW(q = fill_file_queue(mixed_list));
    BOOST_CHECK_EQUAL(q.size() , name_list.size());

    auto niter = name_list.begin();
    while(!q.empty())
    {
        BOOST_CHECK_EQUAL(q.front().path(),*niter++);
        q.pop();
    }
}

BOOST_AUTO_TEST_SUITE_END()
