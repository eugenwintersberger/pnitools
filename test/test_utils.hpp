/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
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
 *
 *  Created on: Oct 10, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <iterator>

/*!
\brief data generating functions

This header file contains a couple of template functions generating data and
storing the result in a container. The container is assumed to have the
appropriate size and exposes an interface common to all STL containers. 
The functions are save in a sense that they iterate ofer the 
*/


/*!
\brief create a range

\f[
    v_i = x_0 + i*d
\f]
\tparam ITER iterator type
\param r instance of CTYPE
\param x0 first value
\param d increment
*/
template<typename ITERT> 
void create_range(ITERT begin,ITERT end,
                  typename std::iterator_traits<ITERT>::value_type x0,
                  typename std::iterator_traits<ITERT>::value_type d)
{
    typedef typename std::iterator_traits<ITERT>::value_type value_type;
    
    auto iter = begin;
    value_type index = 0;
    for(auto iter = begin; iter!= end; ++iter)
        *iter = x0 + (index++)*d;
}

//-----------------------------------------------------------------------------
/*!
\brief create data from function

\f[
    r_i = f(a_i)
\f]

\tparam RITER result iterator type
\tparam AITER argument iterator type
\tparam FTYPE callable type
\param args instance of CTYPE with the arguments
\param f instance of FTYPE evaluated for each new element


*/
template<typename RITER,
         typename AITER,
         typename FTYPE
        >
void create_data(RITER &rbegin,RITER &rend,AITER &abegin,FTYPE &f)
{
    typedef typename std::iterator_traits<RITER>::value_type result_type;
    typedef typename std::iterator_traits<AITER>::value_type args_type;

    auto argiter = abegin;
    auto riter   = rbegin; 

    for(;riter!=rend;++argiter,++riter) *riter = f(*argiter);
}
