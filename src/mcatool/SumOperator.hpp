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
#ifndef __SUMOPERATOR_HPP__
#define __SUMOPERATOR_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ArrayFactory.hpp>
#include <pni/utils/ArrayOperations.hpp>

#include "Operator.hpp"

using namespace pni::utils;

class SumOperator:public Operator
{
    private:
        Float64 _sum;
    public:
        SumOperator(const po::variables_map &config):
            Operator(config),
            _sum(0)
        {}

        ~SumOperator(){}

        virtual void operator()(const Float64Array &channels,
                                const Float64Array &data)
        {
            _sum = pni::utils::sum(data);
        }


        virtual std::ostream &stream_result(std::ostream &o) const
        {
            o<<_sum;
            return o;
        }
};

#endif
