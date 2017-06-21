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

namespace fs = boost::filesystem;

struct detinfo_fixture
{
    fs::path command_path;
    fs::path tif_file_path;
    fs::path cbf_file_path;
    std::string command;
    std::string output;
    int         return_value;

    detinfo_fixture():
        command_path(bin_path),
        tif_file_path(tif_path),
        cbf_file_path(cbf_path),
        command(),
        output(),
        return_value()
    {
        command_path /= "detinfo";
        tif_file_path /= "detector_%03.tif::16";
        cbf_file_path /= "LAOS3_05461.cbf";
    }
    
    void run_test(const std::string &fmt_option,
                  const fs::path &file_path)
    {
        command = get_command({command_path.string(),fmt_option,
                               file_path.string(),">detinfo_test.tmp"});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());

        output = read_data(fs::path("detinfo_test.tmp"));
        boost::trim(output);

    }
};

BOOST_FIXTURE_TEST_SUITE(detinfo_acceptance_test,detinfo_fixture)

    BOOST_AUTO_TEST_CASE(test_return_values)
    {
        BOOST_TEST_MESSAGE("Execute:"+command_path.string());
        return_value = std::system(command_path.string().c_str());
        BOOST_CHECK_EQUAL(WEXITSTATUS(return_value),1);

        return_value = std::system(get_command({command_path.string(),"bla.txt"}).c_str());
        BOOST_CHECK_EQUAL(WEXITSTATUS(return_value),1);

        return_value = std::system(get_command({command_path.string(),"cmake_install.cmake"}).c_str());
        BOOST_CHECK_EQUAL(WEXITSTATUS(return_value),1);

        fs::path p(tif_path);
        p/="detector_%03i.tif:9:16";
        command = get_command({command_path.string(),p.string()});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(return_value,0);

        p = tif_path;
        p/= "detector_%03i.fio:1:5";
        command = get_command({command_path.string(),p.string()});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(WEXITSTATUS(return_value),1);

        p = nexus_path;
        p /= "tstfile_00012.h5";
        command = get_command({command_path.string(),p.string()});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(return_value,0);
    }

    BOOST_AUTO_TEST_CASE(test_simple_cbf)
    {
        command = get_command({command_path.string(),"-fsimple",
                               cbf_file_path.string(),">test_simple.tmp"});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(return_value,0);

        output = read_data(fs::path("test_simple.tmp"));
        boost::trim(output);
        BOOST_CHECK_EQUAL(output,cbf_simple_output);
    }
    
    BOOST_AUTO_TEST_CASE(test_simple_tif)
    {
        command = get_command({command_path.string(),"-fsimple",
                               tif_file_path.string(),">test_simple.tmp"});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(return_value,0);

        output = read_data(fs::path("test_simple.tmp"));
        boost::trim(output);
        BOOST_CHECK_EQUAL(output,tif_simple_output);
    }


    BOOST_AUTO_TEST_CASE(test_simple_nexus)
    {
        fs::path p = nexus_path;
        p /= "tstfile_00012.h5";
        command = get_command({command_path.string(),"-fsimple", p.string(),
                               ">test_simple.tmp"});
        BOOST_TEST_MESSAGE("Execute: "+command);
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(return_value,0);

        output = read_data(fs::path("test_simple.tmp"));
        boost::trim(output);
        BOOST_CHECK_EQUAL(output,nexus_simple_output);
    }

    BOOST_AUTO_TEST_CASE(test_kv_cbf)
    {

    }

BOOST_AUTO_TEST_SUITE_END()
