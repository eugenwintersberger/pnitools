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
//  Created on: Jun 20, 2017
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Acceptance test for detinfo
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <cstdlib>
#include <test/config.hpp>
#include <test/command_runner.hpp>
#include <iostream>
#include <pni/io/nexus.hpp>

using namespace pni::io;
using boost::test_tools::output_test_stream;

namespace fs = boost::filesystem;


struct detinfo_fixture
{
    command_runner runner;
    fs::path tif_file_path;
    fs::path cbf_file_path;
    fs::path nx_file_path;
    std::string command;
    std::string output;
    int         return_value;

    detinfo_fixture():
        runner(fs::path(bin_path).append("detinfo")),
        tif_file_path(fs::path(tif_path).append("detector_%03i.tif:9:16")),
        cbf_file_path(fs::path(cbf_path).append("LAOS3_05461.cbf")),
        nx_file_path(fs::path(nexus_path).append("tstfile_00012.h5")),
        output(),
        return_value()
    {
    }
    
};

BOOST_FIXTURE_TEST_SUITE(detinfo_acceptance_test,detinfo_fixture)

    BOOST_AUTO_TEST_CASE(test_return_values)
    {
        runner({});
        BOOST_CHECK_EQUAL(runner.return_value(),1);
        
        runner({"bla.txt"});
        BOOST_CHECK_EQUAL(runner.return_value(),1);

        runner({"cmake_install.cmake"});
        BOOST_CHECK_EQUAL(runner.return_value(),1);
        
        runner({tif_file_path.string()});
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);

        fs::path p(tif_path);
        p/= "detector_%03i.fio:1:5";
        runner({p.string()});
        BOOST_CHECK_EQUAL(runner.return_value(),1);

        runner({nx_file_path.string()});
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
    }

    BOOST_AUTO_TEST_CASE(test_simple_cbf)
    {
        runner({"-fsimple",cbf_file_path.string()});
        output_test_stream stream("cbf_simple_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output=runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());

    }
    
    BOOST_AUTO_TEST_CASE(test_simple_tif)
    {
        runner({"-fsimple",tif_file_path.string()});
        output_test_stream stream("tif_simple_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }


    BOOST_AUTO_TEST_CASE(test_simple_nexus)
    {
        runner({"-fsimple",nx_file_path.string()});
        output_test_stream stream("nexus_simple_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_kv_cbf)
    {
        runner({"-fkeyvalue",cbf_file_path.string()});
        output_test_stream stream("cbf_kv_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_kv_nexus)
    {
        runner({"-fkeyvalue",nx_file_path.string()});
        output_test_stream stream("nexus_kv_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_kv_tif)
    {
        runner({"-fkeyvalue",tif_file_path.string()});
        output_test_stream stream("tif_kv_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }
    
    BOOST_AUTO_TEST_CASE(test_csv_cbf)
    {
        runner({"-fcsv",cbf_file_path.string()});
        output_test_stream stream("cbf_csv_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_csv_nexus)
    {
        runner({"-fcsv",nx_file_path.string()});
        output_test_stream stream("nexus_csv_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_csv_tif)
    {
        runner({"-fcsv",tif_file_path.string()});
        output_test_stream stream("tif_csv_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }
    
    BOOST_AUTO_TEST_CASE(test_xml_cbf)
    {
        runner({"-fxml",cbf_file_path.string()});
        output_test_stream stream("cbf_xml_output.pattern");
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_xml_nexus)
    {
        runner({"-fxml",nx_file_path.string()});
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output_test_stream stream("nexus_xml_output.pattern");
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

    BOOST_AUTO_TEST_CASE(test_xml_tif)
    {
        runner({"-fxml",tif_file_path.string()});
        BOOST_CHECK_EQUAL(runner.return_value(),SUCCESS_RETURN);
        output_test_stream stream("tif_xml_output.pattern");
        output = runner.output();
        boost::trim(output);
        stream<<output;
        BOOST_CHECK(stream.match_pattern());
    }

BOOST_AUTO_TEST_SUITE_END()
