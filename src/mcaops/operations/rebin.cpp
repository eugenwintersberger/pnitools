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

#include <pni/core/configuration.hpp>
#include "rebin.hpp"

using namespace pni::core;

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
       
//-----------------------------------------------------------------------------
void rebin::operator()(const argument_type &data)
{
    data_range channel_range = data.first;
    data_range mca_range     = data.second;

    //compute the number of bins for the new histogramq
    size_t nchannels = std::distance(channel_range.first,channel_range.second);
    size_t size = (nchannels - nchannels%_bsize) /_bsize;
    //if the size of the original histogram is not an integer multiple
    //of the new bin size add an additional channel to collect the
    //residual channels
    if(nchannels%_bsize != 0) size++;
   
    //create output data and initialize it with 0
    _channels = array_type::create(shape_type{{size}});
    _data = array_type::create(shape_type{{size}});
    
    std::fill(_data.begin(),_data.end(),0);
    std::fill(_channels.begin(),_channels.end(),0);

    //start with rebinning loop
    size_t new_index = 0;
    for(size_t i=0;i<nchannels;i++)
    {
        if((i%_bsize == 0)&&i)
        {
            //normalize rebined data
            if(_norm) _data[new_index] /= _bsize;

            //normaliz rebind center bin positions
            if(_noxrebin)
                _channels[new_index] = new_index;
            else
                _channels[new_index] /= _bsize;

            //increment index of the new histogram
            new_index++;
        }

        //add content to the new bin positions
        _data[new_index] += *(mca_range.first+i);
        _channels[new_index] += *(channel_range.first+i);

    }

    //when we are done we have to manage the last bin 
    if(nchannels%_bsize != 0)
    {
        if(_norm)
            _data[new_index] /= nchannels%_bsize;

        if(_noxrebin) 
            _channels[new_index] = new_index; 
        else
            _channels[new_index] /= nchannels%_bsize;
    }
    else
    {
        if(_noxrebin) 
            _channels[new_index] = new_index;
        else
            _channels[new_index] /= _bsize;
    }

    
}


//-----------------------------------------------------------------------------
std::ostream &rebin::stream_result(std::ostream &o) const
{
    for(size_t i=0;i<_channels.size();i++)
    {
        o<<_channels[i]<<"\t"<<_data[i]<<std::endl;
    }
    return o;
}
