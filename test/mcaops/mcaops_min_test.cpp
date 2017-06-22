//
// (c) Copyright 2017 DESY
//
// This file is part of pniio.
//
// pniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pniio.  If not, see <http://www.gnu.org/licenses/>.
// 
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created: Thu 22 Jun, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE acceptance test for mcaops min operation
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <pni/io/parsers.hpp>
#include <pni/io/container_io_config.hpp>
#include <pni/core/types.hpp>
#include <vector>


#include <test/config.hpp>
#include <test/command_fixture.hpp>

#include "common.hpp"

namespace fs = boost::filesystem;
using namespace pni::io;
using namespace pni::core;
    
using mins_t   = std::vector<float64>;
using parser_t = parser<mins_t>;

static parser_t min_parser;
static mins_t total_mins;
static mins_t roi1_mins;
static mins_t roi2_mins;

struct mcaops_global_fixture 
{

    mcaops_global_fixture()
    {
        min_parser = parser_t(container_io_config('\n'));
        total_mins = min_parser(read_data(total_min_file.string()));
        roi1_mins = min_parser(read_data(roi1_min_file.string())); 
        roi2_mins = min_parser(read_data(roi2_min_file.string()));
    }

    virtual ~mcaops_global_fixture()
    {}
};

BOOST_GLOBAL_FIXTURE(mcaops_global_fixture);

struct mcaops_min_fixture : public command_fixture
{
    fs::path fio_range_1;
    fs::path fio_range_2;

    mcaops_min_fixture():
        command_fixture(),
        fio_range_1(fio_path),
        fio_range_2(fio_path)
    {
        command_path /= "mcaops";
        fio_range_1 /= filename_format;
        fio_range_1 += file_range_1;
        fio_range_2 /= filename_format;
        fio_range_2 += file_range_2;
    }
};

BOOST_FIXTURE_TEST_SUITE(mcaops_mintest,mcaops_min_fixture)
    
    // ======================testing with input from a Nexus file=============
    BOOST_AUTO_TEST_SUITE(nexus_input)
        BOOST_AUTO_TEST_CASE(test_total_result)
        {
            run_command({base_opt,mca_opt,"min","fiodata.nxs"});
            BOOST_CHECK_EQUAL(get_return_value(return_value),0);
        
            boost::trim(output);
            mins_t mins = min_parser(output);
            BOOST_CHECK_EQUAL_COLLECTIONS(mins.begin(),mins.end(),
                                          total_mins.begin(),total_mins.end());
        }

        BOOST_AUTO_TEST_CASE(test_roi1_result)
        {
            run_command({roi1_opt,base_opt,mca_opt,"min","fiodata.nxs"});
            BOOST_CHECK_EQUAL(get_return_value(return_value),0);
        
            boost::trim(output);
            mins_t mins = min_parser(output);
            BOOST_CHECK_EQUAL_COLLECTIONS(mins.begin(),mins.end(),
                                          roi1_mins.begin(),roi1_mins.end());
        }

        BOOST_AUTO_TEST_CASE(test_roi2_result)
        {
            run_command({roi2_opt,base_opt,mca_opt,"min","fiodata.nxs"});
            BOOST_CHECK_EQUAL(get_return_value(return_value),0);
        
            boost::trim(output);
            mins_t mins = min_parser(output);
            BOOST_CHECK_EQUAL_COLLECTIONS(mins.begin(),mins.end(),
                                          roi2_mins.begin(),roi2_mins.end());
        }
    BOOST_AUTO_TEST_SUITE_END()

    //================testing with input from fio files======================
    BOOST_AUTO_TEST_SUITE(fio_input)
        BOOST_AUTO_TEST_CASE(test_total_result)
        {
            run_command({"min",fio_range_1.string(),fio_range_2.string()});
            BOOST_CHECK_EQUAL(get_return_value(return_value),0);
        
            boost::trim(output);
            mins_t mins = min_parser(output);
            BOOST_CHECK_EQUAL_COLLECTIONS(mins.begin(),mins.end(),
                                          total_mins.begin(),total_mins.end());
        }

        BOOST_AUTO_TEST_CASE(test_roi1_result)
        {
            run_command({roi1_opt,"min",fio_range_1.string(),
                                        fio_range_2.string()});
            BOOST_CHECK_EQUAL(get_return_value(return_value),0);
        
            boost::trim(output);
            mins_t mins = min_parser(output);
            BOOST_CHECK_EQUAL_COLLECTIONS(mins.begin(),mins.end(),
                                          roi1_mins.begin(),roi1_mins.end());
        }

        BOOST_AUTO_TEST_CASE(test_roi2_result)
        {
            run_command({roi2_opt,"min",fio_range_1.string(),
                                        fio_range_2.string()});
            BOOST_CHECK_EQUAL(get_return_value(return_value),0);
        
            boost::trim(output);
            mins_t mins = min_parser(output);
            BOOST_CHECK_EQUAL_COLLECTIONS(mins.begin(),mins.end(),
                                          roi2_mins.begin(),roi2_mins.end());
        }
    BOOST_AUTO_TEST_SUITE_END()

    //================testing by reading from standard input ==================
    BOOST_AUTO_TEST_SUITE(stdin_input)

        BOOST_AUTO_TEST_CASE(test_total_result)
        {
            auto iter = total_mins.begin();
            for(auto p: stdin_files)
            {
                fs::path ifile(stdin_path);
                ifile /= p;
                run_command({"min","<"+ifile.string()});
                BOOST_CHECK_EQUAL(get_return_value(return_value),0);
                boost::trim(output);
                mins_t mins = min_parser(output);
                BOOST_CHECK_EQUAL(mins.size(),1);
                BOOST_CHECK_CLOSE(mins[0],*iter,0.001);
                iter++;
            }
        }

        BOOST_AUTO_TEST_CASE(test_roi1_result)
        {
            auto iter = roi1_mins.begin();
            for(auto p: stdin_files)
            {
                fs::path ifile(stdin_path);
                ifile /= p;
                run_command({roi1_opt,"min","<"+ifile.string()});
                BOOST_CHECK_EQUAL(get_return_value(return_value),0);
                boost::trim(output);
                mins_t mins = min_parser(output);
                BOOST_CHECK_EQUAL(mins.size(),1);
                BOOST_CHECK_CLOSE(mins[0],*iter,0.001);
                iter++;
            }
        }
        
        BOOST_AUTO_TEST_CASE(test_roi2_result)
        {
            auto iter = roi2_mins.begin();
            for(auto p: stdin_files)
            {
                fs::path ifile(stdin_path);
                ifile /= p;
                run_command({roi2_opt,"min","<"+ifile.string()});
                BOOST_CHECK_EQUAL(get_return_value(return_value),0);
                boost::trim(output);
                mins_t mins = min_parser(output);
                BOOST_CHECK_EQUAL(mins.size(),1);
                BOOST_CHECK_CLOSE(mins[0],*iter,0.001);
                iter++;
            }
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
