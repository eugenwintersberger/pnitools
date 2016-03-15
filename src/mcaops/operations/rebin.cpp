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
#include "../../common/algorithms/rebin.hpp"
#include "rebin.hpp"

using namespace pni::core;

//----------------------------------------------------------------------------
operation::array_type rebin::create_array(size_t size)
{
    auto a = array_type::create(shape_t{size});
    std::fill(a.begin(),a.end(),0);

    return a;
}

//----------------------------------------------------------------------------
size_t rebin::get_new_channels(size_t orig_channels) const
{
    size_t residuum = orig_channels%_bsize;
    size_t new_size = (orig_channels - residuum) /_bsize;

    //if the size of the original histogram is not an integer multiple
    //of the new bin size add an additional channel to collect the
    //residual channels
    if(residuum) new_size++;

    return new_size;
}

//----------------------------------------------------------------------------
configuration create_config()
{
    configuration c;

    c.add_option(config_option<size_t>("binsize","b",
                "Number of bins to collate!",1));
    c.add_option(config_option<bool>("noxrebin","",
                "no x-axis rebinning",false));
    c.add_option(config_option<bool>("normalize","",
                "normalize the input data",false));

    return c;
}
       
//-----------------------------------------------------------------------------
rebin::rebin():
        operation(),
        _bsize(0),
        _noxrebin(false),
        _norm(false)
{

}

//-----------------------------------------------------------------------------
operation::args_vector rebin::configure(const args_vector &args) 
{
    configuration c = create_config();
    args_vector unused = parse(c,args,true);

    _bsize    = c.value<size_t>("binsize");
    _noxrebin = c.value<bool>("noxrebin");
    _norm     = c.value<bool>("normalize");

    return unused;
}

//----------------------------------------------------------------------------
size_t rebin::distance(data_range range)
{
    return std::distance(range.first,range.second);
}

//----------------------------------------------------------------------------
operation::array_type rebin::create_norm(size_t orig_channels,
                                         size_t new_channels) const
{
    array_type n = create_array(new_channels);
    std::fill(n.begin(),n.end(),_bsize);

    if(orig_channels%_bsize) n.back() = orig_channels%_bsize;

    return n;
}

       
//-----------------------------------------------------------------------------
void rebin::operator()(const argument_type &data)
{
    data_range channel_range = data.first;
    data_range mca_range     = data.second;
   
    //create output data and initialize it with 0
    array_type::storage_type mca_storage;
    array_type::storage_type channel_storage;

    algorithms::rebin(mca_range.first,mca_range.second,
                      std::back_inserter(mca_storage),_bsize,_norm);

    if(!_noxrebin)
        algorithms::rebin(channel_range.first,channel_range.second,
                          std::back_inserter(channel_storage),_bsize,true);

    shape_t shape{mca_storage.size()};
    _new_channels = array_type::create(shape,std::move(channel_storage));
    _new_mca      = array_type::create(shape,std::move(mca_storage));
}


//-----------------------------------------------------------------------------
std::ostream &rebin::stream_result(std::ostream &o) const
{
    const output_config &c = this->output_configuration();

    for(size_t i=0;i<_new_channels.size();i++)
    {
        if(c.channel_output())
            o<<_new_channels[i]<<"\t";
        
        o<<_new_mca[i]<<c.channel_separator();
    }
    return o;
}
