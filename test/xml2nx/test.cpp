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
#define BOOST_TEST_MODULE xml2nx test case
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/filesystem.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>

#include <test/config.hpp>
#include <test/command_fixture.hpp>

using namespace pni::core;
using namespace pni::io::nx;

namespace fs = boost::filesystem;

struct xml2nx_test_fixture : public command_fixture
{
    fs::path out_file; 
    xml2nx_test_fixture():
        command_fixture(),
        out_file("xml2nx.nxs")
    {
        command_path /= "xml2nx";

        fs::remove(out_file); //we need to remove artifacts from the previous
                              //runs
    }

};

template<typename T>
std::vector<T> read(const h5::nxobject &object)
{
    std::vector<T> buffer(get_size(object));
    read(object,buffer);
    return buffer;
}


BOOST_FIXTURE_TEST_SUITE(xml2nx_test,xml2nx_test_fixture)

    void check_basic_setup(const string &filename)
    {
        h5::nxfile f = h5::nxfile::open_file(filename);
        h5::nxgroup cg = f.root()["entry"];
        BOOST_CHECK_EQUAL(read<string>(cg.attributes["NX_class"])[0],"NXentry");
        BOOST_CHECK_EQUAL(read<string>(cg["title"])[0],"Default entry");
        BOOST_CHECK_EQUAL(read<string>(cg["experiment_description"])[0],
                    "This is a plain template which contains the standard field and groups");
        BOOST_CHECK_EQUAL(read<string>(cg["start_time"])[0],"123");
        BOOST_CHECK_EQUAL(read<string>(cg["end_time"])[0],"124");
        BOOST_CHECK_EQUAL(read<string>(cg["program_name"])[0],"xml2nx");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["program_name"],"version"))[0],"0.1.0");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["program_name"],"configuration"))[0],"none");
        cg = get_object(f.root(),"/:NXentry/:NXinstrument");
        BOOST_CHECK_EQUAL(read<string>(cg["name"])[0],"High resolution beamline");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["name"],"short_name"))[0],"P08");
        cg = get_object(f.root(),"/:NXentry/:NXinstrument/source");
        BOOST_CHECK_EQUAL(read<string>(cg["name"])[0],"Positron-Elektron Tandem Ring Anlage III");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["name"],"short_name"))[0],"PETRA III");
        BOOST_CHECK_EQUAL(read<string>(cg["type"])[0],"Synchrotron X-ray Source");
        BOOST_CHECK_EQUAL(read<string>(cg["probe"])[0],"x-ray");

        cg = get_object(f.root(),"/:NXentry");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["sample"],"NX_class"))[0],"NXsample");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["control"],"NX_class"))[0],"NXmonitor");
        BOOST_CHECK_EQUAL(read<string>(
                    get_attribute(cg["data"],"NX_class"))[0],"NXdata");

    }

    void check_detector_setup(const string &filename)
    {
        h5::nxfile f = h5::nxfile::open_file(filename);
        h5::nxgroup det = get_object(f.root(),"/:NXentry/:NXinstrument/:NXdetector");

        BOOST_CHECK_CLOSE(read<double>(det["x_pixel_size"])[0],12.45,0.001);
        BOOST_CHECK_CLOSE(read<double>(det["y_pixel_size"])[0],13.45,0.001);

        h5::nxfield data = det["data"];
        auto s = data.shape<shape_t>();
        BOOST_CHECK_EQUAL(data.rank(),2);
        BOOST_CHECK_EQUAL(s[0],0);
        BOOST_CHECK_EQUAL(s[1],2048);

        BOOST_CHECK_EQUAL(read<string>(det["layout"])[0],"linear");
        BOOST_CHECK_EQUAL(read<string>(det["description"])[0],"PSD");
        BOOST_CHECK_CLOSE(read<double>(det["distance"])[0],0.8,0.001);
        
    }
   
    BOOST_AUTO_TEST_CASE(test_return)
    {
        run_command(option_list{});
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);
        
        option_list options{"-p"+out_file.string()+"://","basic.xml"};
        run_command(options);
        BOOST_TEST_MESSAGE("Executed: "+command);
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        //repeat the last command - should not work as the file exists
        run_command(options);
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);

        options.insert(options.begin(),"-o"); //this should work now
        BOOST_TEST_MESSAGE("Executing: "+command);
        run_command(options);
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        //no result file should cause an error
        run_command({"basic.xml"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);
    }

    BOOST_AUTO_TEST_CASE(test_create_basic)
    {
        run_command({"-o","-p"+out_file.string()+"://","basic.xml"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        check_basic_setup(out_file.string());

    }

    BOOST_AUTO_TEST_CASE(test_append_detector)
    {
        run_command({"-o",
                     "-p" + out_file.string()+"://",
                     "basic.xml"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        run_command({"-p"+out_file.string()+"://:NXentry/:NXinstrument",
                     "detector.xml"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        check_basic_setup(out_file.string());
        check_detector_setup(out_file.string());
    }

BOOST_AUTO_TEST_SUITE_END()

