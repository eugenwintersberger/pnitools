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

#include "io.hpp"

//-----------------------------------------------------------------------------
void read_from_stdin(operation::array_type &channels,operation::array_type &data)
{
    typedef operation::array_type array_type;
    typedef array_type::value_type value_type;
    std::vector<value_type> chvec;
    std::vector<value_type> dvec;
    value_type ch,d;

    while(std::cin>>ch>>d)
    {
        chvec.push_back(ch);
        dvec.push_back(d);
    }

    channels = array_type(operation::shape_type{chvec.size()});
    data = array_type(operation::shape_type{chvec.size()});
    std::copy(chvec.begin(),chvec.end(),channels.begin());
    std::copy(dvec.begin(),dvec.end(),data.begin());
}

//-----------------------------------------------------------------------------
operation::array_type create_channel_data(size_t n)
{
    operation::array_type channels(operation::shape_type{n});

    for(size_t i=0;i<n;i++) channels[i] = float64(i);
    return channels;
}
