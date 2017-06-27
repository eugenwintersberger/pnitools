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
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <cstdlib>
#include <test/config.hpp>
#include <test/detinfo/ref_data.hpp>
#include <iostream>
#include <pni/io/nx/nx.hpp>

using namespace pni::io::nx;

namespace fs = boost::filesystem;


struct detinfo_fixture
{
    fs::path command_path;
    fs::path tif_file_path;
    fs::path cbf_file_path;
    fs::path nx_file_path;
    std::string command;
    std::string output;
    int         return_value;

    detinfo_fixture():
        command_path(bin_path),
        tif_file_path(tif_path),
        cbf_file_path(cbf_path),
        nx_file_path(nexus_path),
        command(),
        output(),
        return_value()
    {
        command_path /= "detinfo";
        tif_file_path /= "detector_%03i.tif:9:16";
        cbf_file_path /= "LAOS3_05461.cbf";
        nx_file_path /= "tstfile_00012.h5";
    }
    
    void run_test(const std::string &fmt_option,
                  const fs::path &file_path,
                  const fs::path &tmpfile = fs::path("detinfo_test.tmp"))
    {
        command = get_command({command_path.string(),fmt_option,
                               file_path.string(),">"+tmpfile.string()});
        std::cout<<"Execute: "<<command<<std::endl;
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());

        output = read_data(tmpfile);
        boost::trim(output);

    }
};

BOOST_FIXTURE_TEST_SUITE(detinfo_acceptance_test,detinfo_fixture)

    BOOST_AUTO_TEST_CASE(test_return_values)
    {
        BOOST_TEST_MESSAGE("Execute:"+command_path.string());
        return_value = std::system(command_path.string().c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        return_value = std::system(get_command({command_path.string(),"bla.txt"}).c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        return_value = std::system(get_command({command_path.string(),"cmake_install.cmake"}).c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        fs::path p(tif_path);
        p/="detector_%03i.tif:9:16";
        command = get_command({command_path.string(),p.string()});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),SUCCESS_RETURN);

        p = tif_path;
        p/= "detector_%03i.fio:1:5";
        command = get_command({command_path.string(),p.string()});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        p = nexus_path;
        p /= "tstfile_00012.h5";
        command = get_command({command_path.string(),p.string()});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),SUCCESS_RETURN);
    }

    BOOST_AUTO_TEST_CASE(test_simple_cbf)
    {
        run_test("-fsimple",cbf_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,cbf_simple_output);
    }
    
    BOOST_AUTO_TEST_CASE(test_simple_tif)
    {
        run_test("-fsimple",tif_file_path);
        BOOST_CHECK_EQUAL(get_return_value(return_value),SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,tif_simple_output);
    }


    BOOST_AUTO_TEST_CASE(test_simple_nexus)
    {
        run_test("-fsimple",nx_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,nexus_simple_output);
    }

    BOOST_AUTO_TEST_CASE(test_kv_cbf)
    {
        run_test("-fkeyvalue",cbf_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,cbf_kv_output);
    }

    BOOST_AUTO_TEST_CASE(test_kv_nexus)
    {
        run_test("-fkeyvalue",nx_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,nexus_kv_output);
    }

    BOOST_AUTO_TEST_CASE(test_kv_tif)
    {
        run_test("-fkeyvalue",tif_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,tif_kv_output);
    }
    
    BOOST_AUTO_TEST_CASE(test_csv_cbf)
    {
        run_test("-fcsv",cbf_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,cbf_csv_output);
    }

    BOOST_AUTO_TEST_CASE(test_csv_nexus)
    {
        run_test("-fcsv",nx_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,nexus_csv_output);
    }

    BOOST_AUTO_TEST_CASE(test_csv_tif)
    {
        run_test("-fcsv",tif_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,tif_csv_output);
    }
    
    BOOST_AUTO_TEST_CASE(test_xml_cbf)
    {
        run_test("-fxml",cbf_file_path,fs::path("cbf_xml.tmp"));
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,cbf_xml_output);
    }

    BOOST_AUTO_TEST_CASE(test_xml_nexus)
    {
        run_test("-fxml",nx_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,nexus_xml_output);
    }

    BOOST_AUTO_TEST_CASE(test_xml_tif)
    {
        run_test("-fxml",tif_file_path);
        BOOST_CHECK_EQUAL(return_value,SUCCESS_RETURN);
        BOOST_CHECK_EQUAL(output,tif_xml_output);
    }

BOOST_AUTO_TEST_SUITE_END()
