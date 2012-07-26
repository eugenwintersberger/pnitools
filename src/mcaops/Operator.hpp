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
#ifndef __OPERATOR_HPP__
#define __OPERATOR_HPP__

#include <iostream>
#include<boost/program_options/variables_map.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/DArray.hpp>
#include <pni/utils/NumArray.hpp>

using namespace pni::utils;
namespace po = boost::program_options;

class Operator
{
    public:
        //=================public types========================================
        typedef DArray<Float64> array_type;
        typedef NumArray<array_type> narray_type;
        typedef std::vector<size_t> shape_type;
        //---------------------------------------------------------------------
        Operator(const po::variables_map &config){}

        //---------------------------------------------------------------------
        virtual ~Operator() {}

        //---------------------------------------------------------------------
        virtual void operator()(const array_type &channels,
                                const array_type &data) = 0;

        //---------------------------------------------------------------------
        virtual std::ostream &stream_result(std::ostream &o) const = 0;
};

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const Operator &op)
{
    return op.stream_result(o);
}

#endif
