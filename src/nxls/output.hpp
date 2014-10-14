//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include "output_config.hpp"

using namespace pni::core;
using namespace pni::io::nx;

class output
{
    private:
        std::ostream &_stream;
        output_config _config;

        template<typename OTYPE>
        void attribute_output(const OTYPE &parent);

        string get_path(const h5::nxobject &o) const;

    public:
        explicit output(std::ostream &stream,
                        const output_config &config);
    
        template<typename OTYPE>
        void operator()(const OTYPE &parent);
};

string get_metadata(const h5::nxobject &o);
string get_field_metadata(const h5::nxobject &o);
string get_group_metadata(const h5::nxobject &o);
string get_attribute_metadata(const h5::nxobject &o);
string get_data_metadata(const h5::nxobject &o);

//----------------------------------------------------------------------------
template<typename OTYPE>
void output::attribute_output(const OTYPE &parent)
{
    for(auto attribute: parent.attributes)
    {
        if(_config.long_output()) 
            _stream<<get_metadata(h5::nxobject(attribute));

        _stream<<get_path(attribute)<<std::endl;
    }
}

//----------------------------------------------------------------------------
template<typename OTYPE>
void output::operator()(const OTYPE &parent)
{
    for(auto child: parent) 
    {
        if(_config.long_output()) _stream<<get_metadata(child);

        _stream<<get_path(child)<<std::endl;
        if(_config.with_attributes())
        {
            if(is_group(child))
                attribute_output(as_group(child));
            else if(is_field(child))
                attribute_output(as_field(child));
        }

    }
}
