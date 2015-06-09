//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: 8 May, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include "grid_generator_builder.hpp"
#include "grid_generator.hpp"

using namespace pni::core;
float64 grid_generator_builder::get_first_value(const configuration &config)
{
    if(config.has_option("begin"))
        return config.value<float64>("begin");
    else
        throw cli_option_error(EXCEPTION_RECORD,
                "Missing --begin option with x-grid first value!");

}

//----------------------------------------------------------------------------
float64 grid_generator_builder::get_last_value(const configuration &config)
{
    if(config.has_option("end"))
        return config.value<float64>("end");
    else
        throw cli_option_error(EXCEPTION_RECORD,
                "Missing --end option with x-grid final value!");

}

//----------------------------------------------------------------------------
size_t grid_generator_builder::get_npoints(const configuration &config)
{
    if(config.has_option("steps"))
        return config.value<size_t>("steps");
    else
        throw cli_option_error(EXCEPTION_RECORD,
                "Missing --steps option with number of grid points!");
}

//----------------------------------------------------------------------------
float64 grid_generator_builder::get_delta(float64 first,float64 last,size_t npoints)
{
    //need to do a range check here
    if(first>=last)
        throw range_error(EXCEPTION_RECORD,
                "The first value of the grid must be smaller than the last one!");

    return (last-first)/float64(npoints-1);

}

//----------------------------------------------------------------------------
grid_generator grid_generator_builder::build(const configuration &config)
{
    float64 first_value = get_first_value(config);
    float64 last_value  = get_last_value(config);
    size_t  npoints     = get_npoints(config);
    float64 delta       = get_delta(first_value,last_value,npoints);

    return grid_generator(first_value,delta);
}
