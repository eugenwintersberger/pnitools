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
//************************************************************************
//
//  Created on: Jun 1, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>

#include <common/file_type.hpp>


BOOST_AUTO_TEST_SUITE(file_type_test)

BOOST_AUTO_TEST_CASE(tif_test)
{
    BOOST_CHECK(get_file_type("../../data/tif/detector_013.tif") ==
                      file_type::TIFF_FILE);
}

BOOST_AUTO_TEST_CASE(cbf_test)
{
    BOOST_CHECK(get_file_type("../../data/cbf/LAOS3_05461.cbf") == 
                file_type::CBF_FILE);
}

BOOST_AUTO_TEST_CASE(nexus_test)
{
    BOOST_CHECK(get_file_type("../../data/nexus/CSP93065.nxs") == 
                file_type::NEXUS_FILE);
    BOOST_CHECK(get_file_type("../../data/nexus/tstfile_00012.h5") == 
                file_type::NEXUS_FILE);
}

BOOST_AUTO_TEST_CASE(fio_test)
{
    BOOST_CHECK(get_file_type("../../data/fio/scan_mca_00007.fio") == 
                file_type::FIO_FILE);
}

BOOST_AUTO_TEST_CASE(unkown_test)
{
    BOOST_CHECK(get_file_type("common_test") == file_type::UNKNOWN);
}

BOOST_AUTO_TEST_SUITE_END()

