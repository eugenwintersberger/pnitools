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
//  Created on: Jun 9, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <src/nxls/dataset_metadata.hpp>

using namespace pni::core;
using namespace pni::io;

struct DatasetMetadataTestFixture
{
    DatasetMetadataTestFixture()
    {
      h5file = nexus::create_file("DatasetMetadataTest.nxs",hdf5::file::AccessFlags::TRUNCATE);
      root_group = h5file.root();

      scalar_space = hdf5::dataspace::Scalar();
      simple_space = hdf5::dataspace::Simple({10,4});

      int32_type = hdf5::datatype::create<int32>();
      float32_type = hdf5::datatype::create<float32>();

      vstr_type = hdf5::datatype::String::variable();
      fstr_type = hdf5::datatype::String::fixed(10);
      vstr_type.encoding(hdf5::datatype::CharacterEncoding::UTF8);
      vstr_type.padding(hdf5::datatype::StringPad::NULLTERM);

      fstr_type.encoding(hdf5::datatype::CharacterEncoding::ASCII);
      fstr_type.padding(hdf5::datatype::StringPad::NULLPAD);

    }

    hdf5::file::File h5file;
    hdf5::node::Group root_group;
    hdf5::dataspace::Scalar scalar_space;
    hdf5::dataspace::Simple simple_space;
    hdf5::datatype::Integer int32_type;
    hdf5::datatype::Float   float32_type;
    hdf5::datatype::String  vstr_type;
    hdf5::datatype::String  fstr_type;

    hdf5::node::Dataset create_dataset(const hdf5::datatype::Datatype &type,
                                               const hdf5::dataspace::Dataspace &space)
    {
      return hdf5::node::Dataset(root_group,"test_dataset",type,space);
    }


};

BOOST_FIXTURE_TEST_SUITE(DatasetMetadataTest,DatasetMetadataTestFixture)

BOOST_AUTO_TEST_CASE(test_scalar_dataset)
{
  hdf5::node::Dataset dataset = create_dataset(int32_type,scalar_space);

  DatasetMetadata metadata(dataset);
  BOOST_CHECK_EQUAL(metadata.path(),nexus::Path::from_string("DatasetMetadataTest.nxs://test_dataset"));
  BOOST_CHECK_EQUAL(metadata.type_id(),type_id_t::INT32);
  shape_t shape = metadata.shape();
  BOOST_CHECK_EQUAL(shape.size(),1);
  BOOST_CHECK_EQUAL(shape[0],1);
}

BOOST_AUTO_TEST_CASE(test_multidim_dataset)
{
  hdf5::node::Dataset dataset = create_dataset(float32_type,simple_space);

  DatasetMetadata metadata(dataset);
  BOOST_CHECK_EQUAL(metadata.path(),nexus::Path::from_string("DatasetMetadataTest.nxs://test_dataset"));
  BOOST_CHECK_EQUAL(metadata.type_id(),type_id_t::FLOAT32);
  shape_t shape = metadata.shape();
  BOOST_CHECK_EQUAL(shape.size(),2);
  BOOST_CHECK_EQUAL(shape[0],10);
  BOOST_CHECK_EQUAL(shape[1],4);
}

BOOST_AUTO_TEST_CASE(test_scalar_vstr_dataset)
{
  hdf5::node::Dataset dataset = create_dataset(vstr_type,scalar_space);
  DatasetMetadata metadata(dataset);

  BOOST_CHECK_EQUAL(metadata.type_id(),type_id_t::STRING);
}

BOOST_AUTO_TEST_CASE(test_scalar_fstr_dataset)
{
  hdf5::node::Dataset dataset = create_dataset(fstr_type,scalar_space);
  DatasetMetadata metadata(dataset);

  BOOST_CHECK_EQUAL(metadata.type_id(),type_id_t::STRING);
}


BOOST_AUTO_TEST_SUITE_END()


