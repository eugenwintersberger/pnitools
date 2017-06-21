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
// Created: Wed 21 Jun, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE nxcat acceptance test
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/filesystem.hpp>
#include <test/config.hpp>
#include <boost/algorithm/string.hpp>
#include <pni/core/types.hpp>
#include <pni/io/parsers.hpp>
#include <cstdlib>

#include "test.hpp"

using namespace pni::core;
using namespace pni::io;
namespace fs = boost::filesystem;

struct nxcat_test_fixture
{
    fs::path command_path;
    fs::path nexus_file;
    std::string command;
    std::string output;
    int return_value;

    nxcat_test_fixture():
        command_path(bin_path),
        nexus_file(nexus_path),
        command(),
        output(),
        return_value()
    {

        command_path /= "nxcat";
        nexus_file /= "nxls_test.nxs";
    }

    void run_test(const std::vector<std::string> &options,
                  const fs::path &tmpfile = fs::path("tmpfile.txt"))
    {
        std::vector<std::string> l{command_path.string()};
        std::copy(options.begin(),options.end(),std::back_inserter(l));
        l.push_back(">"+tmpfile.string());
        return_value = std::system(get_command(l).c_str());

        output = read_data(tmpfile);
    }

};

BOOST_FIXTURE_TEST_SUITE(nxcat_test,nxcat_test_fixture)

    
    BOOST_AUTO_TEST_CASE(test_return_values)
    {
        // no argumens at all
        command = get_command({command_path.string()});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        // file does not exist
        command = get_command({command_path.string(),"blabla.tif"});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);
    
        // file is not a NeXus file
        command = get_command({command_path.string(),
                               command_path.string()});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        // the target bject is nof a field or attribute
        fs::path p(nexus_file);
        p += "://:NXentry";

        command = get_command({command_path.string(),p.string()});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        p = nexus_file;
        p += "://:NXentry/program_name";
        command = get_command({command_path.string(),p.string()});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

    }

    BOOST_AUTO_TEST_CASE(test_read_string_field)
    {
        fs::path p = nexus_file;
        p += "://:NXentry/program_name";
        run_test({p.string()}); 
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        boost::trim(output);
        BOOST_CHECK_EQUAL(output,"xml2nx");
    }

    BOOST_AUTO_TEST_CASE(test_read_string_attribute)
    {
        fs::path p = nexus_file;
        p += "://:NXentry/program_name@version";
        run_test({p.string()});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        boost::trim(output);
        BOOST_CHECK_EQUAL(output,"0.1.0");
    }
    
    BOOST_AUTO_TEST_CASE(test_read_float_field)
    {
        fs::path p = nexus_file;
        p += "://:NXentry/:NXinstrument/:NXdetector/x_pixel_size";
        run_test({p.string()});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);
    
        boost::trim(output);
        parser<float64> pr;
        BOOST_CHECK_CLOSE(pr(output),12.45,0.0001);
            
    }

    BOOST_AUTO_TEST_CASE(test_read_float_array_field)
    {
        fs::path p = nexus_path;
        p /= "tstfile_00012.h5://:NXentry/:NXinstrument/channel_1/polar_angle";
        run_test({p.string()});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        boost::trim(output);
        std::cout<<output<<std::endl;
        std::stringstream ss(output);
        
        parser<float64> pr;
        auto ref_iter = polar_angles.begin();
        while(!ss.eof())
        {
            std::string line_buffer;
            std::getline(ss,line_buffer);
            boost::trim(line_buffer);
            BOOST_CHECK_CLOSE(pr(line_buffer),*ref_iter,0.001);
            ref_iter++;
        }


    }

BOOST_AUTO_TEST_SUITE_END()
