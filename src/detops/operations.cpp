/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Oct 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <algorithm>
#include "operations.hpp"

//-----------------------------------------------------------------------------
void min_operation(const array_t &data)
{
    
}

//-----------------------------------------------------------------------------
void max_operation(const array_t &data)
{

}

//-----------------------------------------------------------------------------
void average_operation(const array_t &data)
{
    array_t::value_type result=0.0;

    result =  std::accumulate(data.begin(),data.end(),result);
    result /= array_t::value_type(data.size());

    //print result
}

//-----------------------------------------------------------------------------
void sum_operation(const array_t &data)
{
    array_t::value_type result = 0.0;

    result = std::accumulate(data.begin(),data.end(),result);

    //print result
}
