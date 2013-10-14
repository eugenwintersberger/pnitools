/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
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

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "file_list_parser_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(file_list_parser_test);

//-----------------------------------------------------------------------------
void file_list_parser_test::setUp()
{
    name_list = std::vector<string>{"data/fio/scan_mca_00001.fio",
                                    "data/fio/scan_mca_00002.fio",
                                    "data/fio/scan_mca_00003.fio",
                                    "data/fio/scan_mca_00004.fio",
                                    "data/fio/scan_mca_00005.fio",
                                    "data/fio/scan_mca_00006.fio",
                                    "data/fio/scan_mca_00007.fio",
                                    "data/fio/scan_mca_00008.fio"};
    range_list = std::vector<string>{"data/fio/scan_mca_%05i.fio:1:9"};
    mixed_list = std::vector<string>();
    mixed_list.push_back("data/fio/scan_mca_00001.fio");
    mixed_list.push_back("data/fio/scan_mca_00002.fio");
    mixed_list.push_back("data/fio/scan_mca_%05i.fio:3:8");
    mixed_list.push_back("data/fio/scan_mca_00008.fio");
}

//-----------------------------------------------------------------------------
void file_list_parser_test::tearDown() { }


//-----------------------------------------------------------------------------
void file_list_parser_test::test_parse_list()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    result_list = file_list_parser::parse<result_t>(name_list);
    auto niter = name_list.begin();
    for(auto  iter = result_list.begin();
              iter != result_list.end(); ++iter,++niter)
        CPPUNIT_ASSERT(iter->path() == *niter);
}

//-----------------------------------------------------------------------------
void file_list_parser_test::test_parse_range()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    result_list = file_list_parser::parse<result_t>(range_list);
    CPPUNIT_ASSERT(result_list.size() == name_list.size());
    auto niter = name_list.begin();
    for(auto iter = result_list.begin();
             iter != result_list.end();
             ++iter,++niter)
       CPPUNIT_ASSERT(iter->path() == *niter); 
    
}

//-----------------------------------------------------------------------------
void file_list_parser_test::test_parse_mixed()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    result_list = file_list_parser::parse<result_t>(mixed_list);
    CPPUNIT_ASSERT(result_list.size() == name_list.size());
    auto niter = name_list.begin();
    for(auto iter = result_list.begin();
             iter != result_list.end();
             ++iter,++niter)
       CPPUNIT_ASSERT(iter->path() == *niter); 
}
