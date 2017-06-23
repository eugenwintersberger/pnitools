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
#define BOOST_TEST_MODULE acceptance test for mcaops average operation
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
#include <test/command_runner.hpp>

#include "common.hpp"

namespace fs = boost::filesystem;
using namespace pni::io;
using namespace pni::core;
    
using result_t   = std::vector<float64>;
using parser_t = parser<result_t>;

static parser_t result_parser;
static result_t total_result;
static result_t roi1_result;
static result_t roi2_result;
static fs::path fio_range_1;
static fs::path fio_range_2;

struct mcaops_global_fixture 
{

    mcaops_global_fixture()
    {
        result_parser = parser_t(container_io_config('\n'));
        total_result = result_parser(read_data(total_average_file.string()));
        roi1_result = result_parser(read_data(roi1_average_file.string())); 
        roi2_result = result_parser(read_data(roi2_average_file.string()));
    
        //set up the first range FIO files
        fio_range_1 = fs::path(fio_path);
        fio_range_1 /= filename_format;
        fio_range_1 += file_range_1;

        //set up the second range of FIO files
        fio_range_2 = fs::path(fio_path);
        fio_range_2 /= filename_format;
        fio_range_2 += file_range_2;

    }

    virtual ~mcaops_global_fixture()
    {}
};

BOOST_GLOBAL_FIXTURE(mcaops_global_fixture);

struct mcaops_suite_fixture 
{
    command_runner runner;
    result_t result;

    mcaops_suite_fixture():
        runner(fs::path(bin_path).append("mcaops")),
        result()
    {
    }

    void run_test(const cmd_opts_t &opts)
    {
        runner(opts);
        std::string output = runner.output();
        boost::trim(output);
        result = result_parser(output);
    }
};

BOOST_FIXTURE_TEST_SUITE(mcaops_minpos,mcaops_suite_fixture)
    
    // ======================testing with input from a Nexus file=============
    BOOST_AUTO_TEST_SUITE(nexus_input)
        BOOST_AUTO_TEST_CASE(test_total_result)
        {
            run_test({base_opt,mca_opt,"average","fiodata.nxs"});
            BOOST_CHECK_EQUAL(runner.return_value(),0);
            BOOST_CHECK_EQUAL(result.size(),total_result.size());

            auto result_iter = result.begin();
            auto reference_iter = total_result.begin();
            for(;result_iter!=result.end();++result_iter,++reference_iter)
                BOOST_CHECK_CLOSE(*result_iter,*reference_iter,0.0001);

        }

        BOOST_AUTO_TEST_CASE(test_roi1_result)
        {
            run_test({roi1_opt,base_opt,mca_opt,"average","fiodata.nxs"});
            BOOST_CHECK_EQUAL(runner.return_value(),0);

            auto result_iter = result.begin();
            auto reference_iter = roi1_result.begin();
            for(;result_iter!=result.end();++result_iter,++reference_iter)
                BOOST_CHECK_CLOSE(*result_iter,*reference_iter,0.0001);
        }

        BOOST_AUTO_TEST_CASE(test_roi2_result)
        {
            run_test({roi2_opt,base_opt,mca_opt,"average","fiodata.nxs"});
            BOOST_CHECK_EQUAL(runner.return_value(),0);
            
            auto result_iter = result.begin();
            auto reference_iter = roi2_result.begin();
            for(;result_iter!=result.end();++result_iter,++reference_iter)
                BOOST_CHECK_CLOSE(*result_iter,*reference_iter,0.0001);
        }
    BOOST_AUTO_TEST_SUITE_END()

    //================testing with input from fio files======================
    BOOST_AUTO_TEST_SUITE(fio_input)
        BOOST_AUTO_TEST_CASE(test_total_result)
        {
            run_test({"average",fio_range_1.string(),fio_range_2.string()});
            BOOST_CHECK_EQUAL(runner.return_value(),0);
            
            auto result_iter = result.begin();
            auto reference_iter = total_result.begin();
            for(;result_iter!=result.end();++result_iter,++reference_iter)
                BOOST_CHECK_CLOSE(*result_iter,*reference_iter,0.0001);
        }

        BOOST_AUTO_TEST_CASE(test_roi1_result)
        {
            run_test({roi1_opt,"average",fio_range_1.string(),
                                     fio_range_2.string()});
            BOOST_CHECK_EQUAL(runner.return_value(),0);
            
            auto result_iter = result.begin();
            auto reference_iter = roi1_result.begin();
            for(;result_iter!=result.end();++result_iter,++reference_iter)
                BOOST_CHECK_CLOSE(*result_iter,*reference_iter,0.0001);
        }

        BOOST_AUTO_TEST_CASE(test_roi2_result)
        {
            run_test({roi2_opt,"average",fio_range_1.string(),
                                      fio_range_2.string()});
            BOOST_CHECK_EQUAL(runner.return_value(),0);
            
            auto result_iter = result.begin();
            auto reference_iter = roi2_result.begin();
            for(;result_iter!=result.end();++result_iter,++reference_iter)
                BOOST_CHECK_CLOSE(*result_iter,*reference_iter,0.0001);
        }
    BOOST_AUTO_TEST_SUITE_END()

    //================testing by reading from standard input ==================
    BOOST_AUTO_TEST_SUITE(stdin_input)

        BOOST_AUTO_TEST_CASE(test_total_result)
        {
            auto iter = total_result.begin();
            for(auto p: stdin_files)
            {
                fs::path ifile(stdin_path);
                ifile /= p;
                run_test({"average","<"+ifile.string()});
                BOOST_CHECK_EQUAL(runner.return_value(),0);
                BOOST_CHECK_EQUAL(result.size(),1);
                BOOST_CHECK_CLOSE(result[0],*iter,0.001);
                iter++;
            }
        }

        BOOST_AUTO_TEST_CASE(test_roi1_result)
        {
            auto iter = roi1_result.begin();
            for(auto p: stdin_files)
            {
                fs::path ifile(stdin_path);
                ifile /= p;
                run_test({roi1_opt,"average","<"+ifile.string()});
                BOOST_CHECK_EQUAL(runner.return_value(),0);
                BOOST_CHECK_EQUAL(result.size(),1);
                BOOST_CHECK_CLOSE(result[0],*iter,0.001);
                iter++;
            }
        }
        
        BOOST_AUTO_TEST_CASE(test_roi2_result)
        {
            auto iter = roi2_result.begin();
            for(auto p: stdin_files)
            {
                fs::path ifile(stdin_path);
                ifile /= p;
                run_test({roi2_opt,"average","<"+ifile.string()});
                BOOST_CHECK_EQUAL(runner.return_value(),0);
                BOOST_CHECK_EQUAL(result.size(),1);
                BOOST_CHECK_CLOSE(result[0],*iter,0.001);
                iter++;
            }
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()