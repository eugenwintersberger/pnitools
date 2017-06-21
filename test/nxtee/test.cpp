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
#define BOOST_TEST_MODULE nxtee acceptance test
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

#include <test/config.hpp>

static const std::vector<int> append_data{1, 2, 3,4, 5, 6,7,8, 9,
                                          10, 11, 12, 13, 14, 15};

static const std::vector<int> replace_data{10, 20, 30, 40, 50, 60, 70, 80, 90, 
                                           100, 110, 120, 130, 140, 150};


namespace fs = boost::filesystem;
using namespace pni::core;
using namespace pni::io::nx;

struct nxtee_test_fixture
{
    fs::path command_path;
    fs::path mca_file;
    std::string command;
    std::string output;
    int return_value;
    
    nxtee_test_fixture():
        command_path(bin_path),
        command(),
        output(),
        return_value()
    {
        command_path /= "nxtee";
        create_file_from_xml(fs::path("nxtee_test.nxs"),fs::path("mca.xml"));
    }
    
    void run_command(const std::vector<std::string> &options,
                     const fs::path &tempfile = fs::path("nxtee_test.tmp"))
    {
        std::vector<std::string> l{command_path.string()};
        std::copy(options.begin(),options.end(),std::back_inserter(l));
        l.push_back(">"+tempfile.string());
        
        command = get_command(l);
        return_value = std::system(command.c_str());
        output = read_data(tempfile);
    }
};


BOOST_FIXTURE_TEST_SUITE(nxtee_test,nxtee_test_fixture)
    
    BOOST_AUTO_TEST_CASE(test_return)
    {
        fs::path p;
        p += "nxtee_test.nxs://:NXentry/:NXinstrument/mca2/data@units";
        run_command({p.string(),"< append.dat"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),1);
    }

    BOOST_AUTO_TEST_CASE(test_append_field)
    {
        fs::path p;
        p += "nxtee_test.nxs://:NXentry/:NXinstrument/mca/data";
        run_command({p.string(),"< append.dat"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        h5::nxfile f = h5::nxfile::open_file("nxtee_test.nxs");
        h5::nxgroup r = f.root();
        h5::nxfield field = get_object(r,":NXentry/:NXinstrument/mca/data");

        std::vector<int> data(field.size());
        field.read(data);
        BOOST_CHECK_EQUAL_COLLECTIONS(data.begin(),data.end(),
                                      append_data.begin(),append_data.end());
    }

    BOOST_AUTO_TEST_CASE(test_replace_field)
    {
        fs::path p;
        p += "nxtee_test.nxs://:NXentry/:NXinstrument/mca2/data";
        run_command({"-r",p.string(),"<replace.dat"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        h5::nxfile f = h5::nxfile::open_file("nxtee_test.nxs");
        h5::nxgroup r = f.root();
        h5::nxfield field = get_object(r,":NXentry/:NXinstrument/mca2/data");

        std::vector<int> data(field.size());
        field.read(data);
        BOOST_CHECK_EQUAL_COLLECTIONS(data.begin(),data.end(),
                                      replace_data.begin(),replace_data.end());

    }

    BOOST_AUTO_TEST_CASE(test_replace_attribute)
    {
        fs::path p;
        p += "nxtee_test.nxs://:NXentry/:NXinstrument/mca2/data@units";
        run_command({"-r",p.string(),"<counts.dat"});
        BOOST_CHECK_EQUAL(get_return_value(return_value),0);

        h5::nxfile f = h5::nxfile::open_file("nxtee_test.nxs");
        h5::nxgroup r = f.root();
        h5::nxattribute attr = get_object(r,":NXentry/:NXinstrument/mca2/data@units");

        std::string buffer;
        attr.read(buffer);
        BOOST_CHECK_EQUAL(buffer,"counts");


    }

    
BOOST_AUTO_TEST_SUITE_END()
