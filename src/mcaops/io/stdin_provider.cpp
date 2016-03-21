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
// Created on: May 21, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include "stdin_provider.hpp"


using namespace pni::core;

stdin_provider :: stdin_provider(size_t mca_size):
    data_provider(),
    _mca_size(mca_size)
{ }

//----------------------------------------------------------------------------
stdin_provider::stdin_provider(size_t mca_size,const index_generator &g):
    data_provider(g),
    _mca_size(mca_size)
{}

//----------------------------------------------------------------------------
stdin_provider :: ~stdin_provider()
{}

//----------------------------------------------------------------------------
bool stdin_provider::finished() const
{
    return std::cin.eof();
}

//----------------------------------------------------------------------------
stdin_provider::value_type stdin_provider::next() 
{
    std::vector<float64> c,m;
   
    index_generator g = create_generator();
    size_t channel_index = 0;
    float64 channel,mca;
    while(!finished())
    {
        if(_mca_size && channel_index &&  !(channel_index % _mca_size)) 
            break;

        string line_buffer;
        getline(std::cin,line_buffer,'\n');
        boost::trim(line_buffer);
        if(line_buffer.empty()) continue;
        std::stringstream s(line_buffer);

        s>>channel;
        if(s.eof())
        {
            mca     = channel;
            channel = g();
        }
        else
            s>>mca;
        
        c.push_back(channel);
        m.push_back(mca);
        channel_index++;

    }

    value_type arg{operation::array_type::create(shape_t{channel_index},
                                                 std::move(c)),
                   operation::array_type::create(shape_t{channel_index},
                                                 std::move(m))};

    return arg;
}

//----------------------------------------------------------------------------
