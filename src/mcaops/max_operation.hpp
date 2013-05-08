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

#include <pni/core/types.hpp>
#include <pni/core/array_operations.hpp>

#include "operation.hpp"

using namespace pni::core;


class max_operation:public operation
{
    private:
        size_t _max_pos;
        float64 _max_value;
    public:
        //---------------------------------------------------------------------
        max_operation():
            operation(),
            _max_pos(0),
            _max_value(0)
        {}

        //---------------------------------------------------------------------
        ~max_operation(){}

        //---------------------------------------------------------------------
        virtual void operator()(const array_type &channels, 
                                const array_type &data)
        {
            _max_pos = pni::core::max_offset(data);
            _max_value = data[_max_pos];
        }

        //---------------------------------------------------------------------
        virtual std::ostream &stream_result(std::ostream &o) const
        {
            o<<_max_pos<<"\t"<<_max_value;
            return o;
        }
};

