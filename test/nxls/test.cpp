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
// Created: Wed 21 Jan, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE nxls acceptance test
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/parsers.hpp>
#include <test/config.hpp>
#include <cstdlib>

namespace fs = boost::filesystem;

using namespace pni::core;
using namespace pni::io::nx;

static std::vector<std::string> simple_output = { 
"instrument:NXinstrument",
"sample:NXsample",
"control:NXmonitor",
"data:NXdata",
"title",
"experiment_description",
"start_time",
"end_time",
"program_name"};

static std::vector<std::string> recursive_output = {
"entry:NXentry",
"entry:NXentry/title",
"entry:NXentry/experiment_description",
"entry:NXentry/start_time",
"entry:NXentry/end_time",
"entry:NXentry/program_name",
"entry:NXentry/sample:NXsample",
"entry:NXentry/control:NXmonitor",
"entry:NXentry/data:NXdata",
"entry:NXentry/data:NXdata/data_1",
"entry:NXentry/data:NXdata/data_2",
"entry:NXentry/data:NXdata/data_3",
"entry:NXentry/instrument:NXinstrument",
"entry:NXentry/instrument:NXinstrument/name",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/data",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/layout",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/description",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance",
"entry:NXentry/instrument:NXinstrument/source:NXsource",
"entry:NXentry/instrument:NXinstrument/source:NXsource/name",
"entry:NXentry/instrument:NXinstrument/source:NXsource/type",
"entry:NXentry/instrument:NXinstrument/source:NXsource/probe"
};

static std::vector<std::string> attribute_output = {
"entry:NXentry",
"entry:NXentry@NX_class",
"entry:NXentry/title",
"entry:NXentry/experiment_description",
"entry:NXentry/start_time",
"entry:NXentry/end_time",
"entry:NXentry/program_name",
"entry:NXentry/program_name@version",
"entry:NXentry/program_name@configuration",
"entry:NXentry/sample:NXsample",
"entry:NXentry/sample:NXsample@NX_class",
"entry:NXentry/control:NXmonitor",
"entry:NXentry/control:NXmonitor@NX_class",
"entry:NXentry/data:NXdata",
"entry:NXentry/data:NXdata@NX_class",
"entry:NXentry/data:NXdata/data_1",
"entry:NXentry/data:NXdata/data_1@units",
"entry:NXentry/data:NXdata/data_2",
"entry:NXentry/data:NXdata/data_3",
"entry:NXentry/instrument:NXinstrument",
"entry:NXentry/instrument:NXinstrument@NX_class",
"entry:NXentry/instrument:NXinstrument/name",
"entry:NXentry/instrument:NXinstrument/name@short_name",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector@NX_class",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/data",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/data@units",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/x_pixel_size@units",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/y_pixel_size@units",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/layout",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/description",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance",
"entry:NXentry/instrument:NXinstrument/detector:NXdetector/distance@units",
"entry:NXentry/instrument:NXinstrument/source:NXsource",
"entry:NXentry/instrument:NXinstrument/source:NXsource@NX_class",
"entry:NXentry/instrument:NXinstrument/source:NXsource/name",
"entry:NXentry/instrument:NXinstrument/source:NXsource/name@short_name",
"entry:NXentry/instrument:NXinstrument/source:NXsource/type",
"entry:NXentry/instrument:NXinstrument/source:NXsource/probe"
}; 

struct nxls_test_fixture
{
    using string_vector = std::vector<std::string>;
    fs::path command_path;
    std::string command;
    std::string output;
    int return_value;
    string_vector output_values;

    nxls_test_fixture():
        command_path(bin_path),
        command(),
        output(),
        return_value(),
        output_values()

    {
        command_path /= "nxls";

        std::sort(simple_output.begin(),simple_output.end());
        std::sort(recursive_output.begin(),recursive_output.end());
        std::sort(attribute_output.begin(),attribute_output.end());

        xml::node n = xml::create_from_file("nxls_test.xml");
        h5::nxfile f =h5::nxfile::create_file("nxls_test.nxs",true);
        h5::nxgroup r = f.root();
        xml::xml_to_nexus(n,r);
        r.close();
        f.close();
    }

    void run_command(const std::vector<std::string> &options,
                  const fs::path &tempfile = fs::path("nxlstest.tmp"))
    {
        std::vector<std::string> l{command_path.string()};
        std::copy(options.begin(),options.end(),std::back_inserter(l));
        l.push_back(">"+tempfile.string());
        
        command = get_command(l);
        return_value = std::system(command.c_str());
        output = read_data(tempfile);
    }

    void output_to_vector()
    {
        boost::trim(output);
        pni::io::parser<string_vector> pr(pni::io::container_io_config('\n'));
        output_values = pr(output);
        std::transform(output_values.begin(),output_values.end(),
                       output_values.begin(),
                       [](const std::string &value) 
                       { 
                         std::string r(value);
                         boost::trim(r); 
                         return r;
                         });
    }
};

BOOST_FIXTURE_TEST_SUITE(nxls_test,nxls_test_fixture)

    BOOST_AUTO_TEST_CASE(test_return_values)
    {
        command = get_command({command_path.string()});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        command = get_command({command_path.string(),"bal.txt"});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        command =get_command({command_path.string(),command_path.string()});
        return_value = std::system(command.c_str());
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);
    }

    BOOST_AUTO_TEST_CASE(test_simple_list)
    {
        fs::path p;
        p += "nxls_test.nxs://entry:NXentry";
        run_command({p.string()});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        output_to_vector();
        BOOST_CHECK_EQUAL(output_values.size(),simple_output.size());
        
        std::sort(output_values.begin(),output_values.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(output_values.begin(),output_values.end(),
                                      simple_output.begin(),simple_output.end());

    }

    BOOST_AUTO_TEST_CASE(test_recursive_list)
    {
        fs::path p;
        p += "nxls_test.nxs://";
        run_command({"-r",p.string()});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        output_to_vector();
        std::sort(output_values.begin(),output_values.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(output_values.begin(),output_values.end(),
                                      recursive_output.begin(),
                                      recursive_output.end());

    }
    
    
    BOOST_AUTO_TEST_CASE(test_attribute_list)
    {
        fs::path p;
        p += "nxls_test.nxs://";
        run_command({"-ra",p.string()});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        output_to_vector();
        std::sort(output_values.begin(),output_values.end());
        BOOST_CHECK_EQUAL_COLLECTIONS(output_values.begin(),output_values.end(),
                                      attribute_output.begin(),
                                      attribute_output.end());
    }
BOOST_AUTO_TEST_SUITE_END()
