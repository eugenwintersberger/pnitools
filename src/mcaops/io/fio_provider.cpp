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
// Created on: May 29, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include "fio_provider.hpp"
#include "index_generator.hpp"
#include <pni/io/exceptions.hpp>

using namespace pni::core;
using namespace pni::io;

fio_provider::fio_provider(const string &filename, 
                           const string &mca_column_name,
                           const string &channel_column_name,
                           size_t channel_offset):
    data_provider(),
    _filename(filename),
    _mca_column(mca_column_name),
    _channel_column(channel_column_name),
    _file_read(false),
    _channel_offset(channel_offset)
{
    if(_mca_column.empty())
        throw key_error(EXCEPTION_RECORD,
                "For FIO files the column with MCA data must be provided!");
}

//----------------------------------------------------------------------------
fio_provider :: ~fio_provider()
{}

//----------------------------------------------------------------------------
bool fio_provider::finished() const
{
    return _file_read;
}

//----------------------------------------------------------------------------
fio_provider::array_type 
fio_provider::get_mca_data(const fio_reader &reader) const
{
    try
    {
        auto mca = reader.column<vector_type>(_mca_column);
        shape_t shape{mca.size()};

        return array_type::create(shape,std::move(mca));

    }
    catch(key_error &error)
    {
        std::cerr<<error<<std::endl;
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
    }
    catch(...)
    {
        std::cerr<<"Unknown error when readint MCA data!"<<std::endl;
    }

    //if we arrive here something went wrong
    throw io_error(EXCEPTION_RECORD,
            "Failed to read MCA data from the file!");

}

//----------------------------------------------------------------------------
fio_provider::array_type
fio_provider::get_channel_data(const fio_reader &reader,size_t n) const
{
    vector_type channels;
    if(!_channel_column.empty())
    {
        try
        {
            //read channel/bin-center data from the file
             channels = reader.column<vector_type>(_channel_column);
            shape_t shape{channels.size()};

            return array_type::create(shape,channels);
        }
        catch(key_error &error)
        {
            std::cerr<<error<<std::endl;
        }
        catch(file_error &error)
        {
            std::cerr<<error<<std::endl;
        }
        catch(...)
        {
            std::cerr<<"Unkown error when reading channel data!"<<std::endl;
        }

        throw io_error(EXCEPTION_RECORD,
                "Failed to read channel data from the file!");
    }
    else
    {
        //generate artificial channel index
        std::generate_n(std::back_inserter(channels),n,index_generator(_channel_offset));
        return array_type::create(shape_t{n},std::move(channels));
    }

}

//----------------------------------------------------------------------------
data_provider::value_type fio_provider::next() 
{
    //change the state
    _file_read = true;
   
    //open the file
    fio_reader reader(_filename);

    //read MCA data from the file
    array_type mca = get_mca_data(reader);

    //read or generate channel/bin-center data
    array_type channels = get_channel_data(reader,mca.size());

    //finally construct the result 
    return value_type{std::move(channels),std::move(mca)};
}

//----------------------------------------------------------------------------
