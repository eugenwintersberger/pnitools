//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 08,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iterator>
#include <pni/core/configuration.hpp>
#include <pni/io/formatters.hpp>
#include "scale.hpp"

using namespace pni::core;

//-----------------------------------------------------------------------------
scale::scale():
    operation(),
    _auto_max{true},
    _center{0},
    _delta{1},
    _cvalue{0},
    _channels{},
    _data{}
{ }

//-----------------------------------------------------------------------------
scale::~scale() {}

//-----------------------------------------------------------------------------
namespace {

    configuration create_config()
    {
        configuration config;
        config.add_option(config_option<size_t>("center","c",
                    "index of center bin"));
        config.add_option(config_option<float64>("delta","d",
                    "size of a bin"));
        config.add_option(config_option<float64>("cvalue","x",
                    "position of the center bin"));

        return config;
    }

}

//-----------------------------------------------------------------------------
operation::args_vector scale::configure(const args_vector &args)
{
    configuration c = create_config();
    args_vector unused = parse(c,args,true);

    _delta = c.value<float64>("delta");
    _cvalue = c.value<float64>("cvalue");

    if(c.has_option("center"))
    {
        _auto_max = false;
        _center = c.value<size_t>("center");
    }
    else
    {
        _auto_max = true;
    }

    return unused;
}

//-----------------------------------------------------------------------------
void scale::operator()(const argument_type &arg)
{
    data_range channel_range = arg.first;
    data_range mca_range = arg.second;

    //create new data array and copy original data - it will not be altered
    //during the operation
    shape_t shape{size_t(std::distance(mca_range.first,mca_range.second))};
    _data = array_type::create(shape);
    std::copy(mca_range.first,mca_range.second,_data.begin());


    //create new array for channel data
    _channels = array_type::create(shape);

    if(_auto_max)
    {
        auto max_iter = std::max_element(mca_range.first,mca_range.second);
        size_t index = std::distance(mca_range.first,max_iter);
        _center = *(channel_range.first+index);
    }

    std::transform(channel_range.first,channel_range.second,_channels.begin(),
                   [this](float64 index)
                   { return this->_cvalue + this->_delta*(index - float64(this->_center)); });
}


//-----------------------------------------------------------------------------
std::ostream &scale::stream_result(std::ostream &o) const
{    
    for(size_t i=0;i<_channels.size();i++)
        o<<pni::io::format(_channels[i])<<" "<<pni::io::format(_data[i])<<std::endl;

    return o;
}
