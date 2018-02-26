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
#include <pni/io/nexus.hpp>

#include <test/config.hpp>
#include <test/command_fixture.hpp>

using namespace pni::core;
using namespace pni::io;

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

template<
         typename T,
         typename H5TYPE>
std::vector<T> read(const H5TYPE &object)
{
    std::vector<T> buffer(object.dataspace().size());
    object.read(buffer);
    return buffer;
}


BOOST_FIXTURE_TEST_SUITE(xml2nx_test,xml2nx_test_fixture)

void check_basic_setup(const string &filename)
{
  hdf5::file::File f = nexus::open_file(filename,hdf5::file::AccessFlags::READWRITE);
  hdf5::node::Group cg = f.root()["entry"];

  BOOST_CHECK_EQUAL(read<string>(cg.attributes["NX_class"])[0],"NXentry");

  hdf5::node::Dataset field = cg.nodes["title"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"Default entry");

  field = cg.nodes["experiment_description"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"This is a plain template which contains the standard field and groups");

  field = cg.nodes["start_time"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"123");

  field = cg.nodes["end_time"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"124");

  field = cg.nodes["program_name"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"xml2nx");
  BOOST_CHECK_EQUAL(read<string>(field.attributes["version"])[0],"0.1.0");
  BOOST_CHECK_EQUAL(read<string>(field.attributes["configuration"])[0],"none");

  nexus::GroupList groups = nexus::get_objects(f.root(),nexus::Path("/:NXentry/:NXinstrument"));
  cg = groups.front();
  field = cg.nodes["name"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"High resolution beamline");
  BOOST_CHECK_EQUAL(read<string>(field.attributes["short_name"])[0],"P08");

  groups = nexus::get_objects(f.root(),nexus::Path("/:NXentry/:NXinstrument/source"));
  cg = groups.front();
  field = cg.nodes["name"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"Positron-Elektron Tandem Ring Anlage III");
  BOOST_CHECK_EQUAL(read<string>(field.attributes["short_name"])[0],"PETRA III");
  field = cg.nodes["type"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"Synchrotron X-ray Source");
  field = cg.nodes["probe"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"x-ray");

  groups = nexus::get_objects(f.root(),nexus::Path("/:NXentry"));
  cg = groups.front();
  BOOST_CHECK_EQUAL(read<string>(cg.nodes["sample"].attributes["NX_class"])[0],"NXsample");
  BOOST_CHECK_EQUAL(read<string>(cg.nodes["control"].attributes["NX_class"])[0],"NXmonitor");
  BOOST_CHECK_EQUAL(read<string>(cg.nodes["data"].attributes["NX_class"])[0],"NXdata");

}

void check_detector_setup(const string &filename)
{
  hdf5::file::File f = nexus::open_file(filename,hdf5::file::AccessFlags::READWRITE);
  nexus::Path detector_paths("/:NXentry/:NXinstrument/:NXdetector");
  nexus::GroupList detectors = nexus::get_objects(f.root(),detector_paths);
  hdf5::node::Group detector = detectors.front();

  hdf5::node::Dataset field = detector.nodes["x_pixel_size"];
  BOOST_CHECK_CLOSE(read<double>(field)[0],12.45,0.001);
  field = detector.nodes["y_pixel_size"];
  BOOST_CHECK_CLOSE(read<double>(field)[0],13.45,0.001);

  hdf5::node::Dataset data = detector.nodes["data"];
  hdf5::dataspace::Simple dataspace = data.dataspace();
  hdf5::Dimensions current_dimensions = dataspace.current_dimensions();
  BOOST_CHECK_EQUAL(dataspace.rank(),2);
  BOOST_CHECK_EQUAL(current_dimensions[0],0);
  BOOST_CHECK_EQUAL(current_dimensions[1],2048);

  field = detector.nodes["layout"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"linear");
  field = detector.nodes["description"];
  BOOST_CHECK_EQUAL(read<string>(field)[0],"PSD");
  field = detector.nodes["distance"];
  BOOST_CHECK_CLOSE(read<double>(field)[0],0.8,0.001);

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

