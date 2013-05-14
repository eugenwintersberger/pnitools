/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: May 08,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "rebin_operation.hpp"
       
//-----------------------------------------------------------------------------
rebin_operation::rebin_operation():
        operation(),
        _bsize(0),
        _noxrebin(false),
        _channels(),
        _data()
{}
       
//-----------------------------------------------------------------------------
void rebin_operation::operator()(const array_type &channels,
                        const array_type &data)
{
    //compute the number of bins for the new histogram
    size_t size = (channels.size()-channels.size()%_bsize)/_bsize;
    //if the size of the original histogram is not an integer multiple
    //of the new bin size add an additional channel to collect the
    //residual channels
    if(channels.size()%_bsize != 0) size++;
   
    //create output data and initialize it with 0
    _channels = array_type(shape_type{size});
    _data = array_type(shape_type{size});
    
    std::fill(_data.begin(),_data.end(),0);
    std::fill(_channels.begin(),_channels.end(),0);

    //start with rebinning loop
    size_t new_index = 0;
    for(size_t i=0;i<channels.size();i++)
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
        _data[new_index] += data[i];
        _channels[new_index] += channels[i];

    }

    //when we are done we have to manage the last bin 
    if(channels.size()%_bsize != 0)
    {
        _data[new_index] /= channels.size()%_bsize;
        if(_noxrebin) 
            _channels[new_index] = new_index; 
        else
            _channels[new_index] /= channels.size()%_bsize;
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
std::ostream &rebin_operation::stream_result(std::ostream &o) const
{
    for(size_t i=0;i<_channels.size();i++)
    {
        o<<_channels[i]<<"\t"<<_data[i]<<std::endl;
    }
    return o;
}
