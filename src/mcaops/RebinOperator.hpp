/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: 03.06.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#ifndef __REBINOPERATOR_HPP__
#define __REBINOPERATOR_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ArrayFactory.hpp>
#include <pni/utils/ArrayOperations.hpp>

#include "Operator.hpp"

using namespace pni::utils;

class RebinOperator:public Operator
{
    private:
        size_t _bsize;
        bool   _noxrebin;
        Float64Array _channels;
        Float64Array _data;
    public:
        //---------------------------------------------------------------------
        RebinOperator(const po::variables_map &config):
            Operator(config),
            _bsize(config["binsize"].as<size_t>()),
            _noxrebin(config["noxrebin"].as<bool>()),
            _channels(),
            _data()
        {}

        //---------------------------------------------------------------------
        ~RebinOperator(){}

        //---------------------------------------------------------------------
        virtual void operator()(const Float64Array &channels,
                                const Float64Array &data)
        {
            //compute new size of the histogram
            size_t size = (channels.size()-channels.size()%_bsize)/_bsize;
            if(channels.size()%_bsize != 0) size++;
            
            _channels = ArrayFactory<Float64>::create(Shape({size}));
            _data = ArrayFactory<Float64>::create(Shape({size}));

            _data = 0;
            _channels = 0;
            size_t new_index = 0;
            for(size_t i=0;i<channels.size();i++)
            {
                if((i%_bsize == 0)&&i)
                {
                    //normalize rebined data
                    _data[new_index] /= _bsize;

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

            //when we are done we have to manage the last been 
            if(channels.size()%_bsize != 0)
            {
                _data[new_index] /= channels.size()%_bsize;
                if(_noxrebin) 
                    _channels[new_index] = new_index; 
                else
                    _channels[new_index] /= channels.size()%_bsize;
            }

            
        }


        //---------------------------------------------------------------------
        virtual std::ostream &stream_result(std::ostream &o) const
        {
            for(size_t i=0;i<_channels.size();i++)
            {
                o<<_channels[i]<<"\t"<<_data[i]<<std::endl;
            }
            return o;
        }
};

#endif
