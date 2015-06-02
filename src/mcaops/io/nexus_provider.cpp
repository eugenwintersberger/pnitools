//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Jun 2, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "nexus_provider.hpp"
#include "index_generator.hpp"
#include <iterator>
#include <pni/io/nx/algorithms.hpp>

using namespace pni::core;
using namespace pni::io::nx;

nexus_provider::nexus_provider(const string &file_name,
                               const string &channel_path,
                               const string &mca_path,
                               size_t channel_offset):
    data_provider(),
    _file(h5::nxfile::open_file(file_name,true)),
    _mca_field(),
    _channel_field(),
    _channel_cache(),
    _spectrum_index(0)
{
    //getting access to the MCA data is absolutely mandatory
    _mca_field = get_object(_file.root(),mca_path);

    if(_mca_field.rank()>=3)
        throw shape_mismatch_error(EXCEPTION_RECORD,
                "The MCA data in the Nexus file must be of rank 1 or 2!");

    //get the MCA data shape and allocate the channel chache buffer
    auto mca_shape = _mca_field.shape<shape_t>();
    _channel_cache = array_type::create(shape_t{mca_shape.back()});
    if(!channel_path.empty())
    {
        _channel_field = get_object(_file.root(),channel_path);
        _channel_field.read(_channel_cache);
    }
    else
    {
        typedef array_type::storage_type storage_type;
        //we assume here that the last dimension of the MCA data runs over 
        //the channel index
        //here we have to create the artificial channel data

        storage_type storage;
        std::generate_n(std::back_inserter(storage),
                        mca_shape.back(),index_generator(channel_offset));

        _channel_cache = array_type::create(shape_t{mca_shape.back()},
                                            storage);
    }
}

//----------------------------------------------------------------------------
nexus_provider::~nexus_provider()
{
    _mca_field.close();
    _channel_field.close();
    _file.close();
}

//----------------------------------------------------------------------------
bool nexus_provider::finished() const
{
    return _spectrum_index>=_mca_field.shape<shape_t>().front();
}

//----------------------------------------------------------------------------
data_provider::value_type nexus_provider::next()
{
    auto mca_shape = _mca_field.shape<shape_t>();
    auto mca=array_type::create(shape_t{mca_shape.back()});

    if(mca_shape.size()==1)
    {
        _mca_field.read(mca);
        //set the spectrum index to a value which causes the next call to 
        //finished to return true
        _spectrum_index = _mca_field.size();
    }
    else
    {
        //increment the spectrum index during selection creation
        _mca_field(_spectrum_index++,slice(0,mca_shape.back())).read(mca);
    }

    return value_type{_channel_cache,mca};
    
}
