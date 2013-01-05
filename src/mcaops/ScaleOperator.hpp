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
#pragma once

#include <pni/core/Types.hpp>
#include <pni/core/ArrayOperations.hpp>

#include "Operator.hpp"

using namespace pni::core;

class ScaleOperator:public Operator
{
    private:
        bool _search_max;
        size_t _center;  //center bin
        Float64 _delta;  //delta value
        Float64 _cvalue; //center value
        array_type _channels;
        array_type _data;
    public:
        //---------------------------------------------------------------------
        ScaleOperator(const po::variables_map &config):
            Operator(config),
            _search_max(true),
            _center(0),
            _delta(1),
            _cvalue(0)
        {
            if(config.count("center"))
            {
                _center = config["center"].as<size_t>();
                _search_max = false;
            }

            if(config.count("delta"))
                _delta = config["delta"].as<Float64>();

            if(config.count("cvalue"))
                _cvalue = config["cvalue"].as<Float64>();
             
        }

        //---------------------------------------------------------------------
        ~ScaleOperator(){}

        //---------------------------------------------------------------------
        virtual void operator()(const array_type &channels,
                                const array_type &data)
        {
            _channels = array_type(channels);
            _data = array_type(data);

            if(_search_max)
                _center = pni::core::max_offset(data);

#ifdef NOFOREACH
            for(auto iter=_channels.begin();iter!=_channels.end();iter++)
            {
                Float64 &v = *iter;
#else
            for(Float64 &v: _channels)
            {
#endif
                v = _cvalue + _delta*(v - _center); 
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

