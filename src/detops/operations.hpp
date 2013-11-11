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

#pragma once

#include <functional>
#include <map>
#include <pni/core/types.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/numarray.hpp>

using namespace pni::core;

//define an array type
typedef numarray<darray<float64>> array_t;
typedef std::function<void(const array_t &)> function_t;

class operation
{
    private:
        array_t background_image;
        array_t mask_image;
        array_t::value_type norm_factor;
        std::function_t function;
    public:
        operation();
        virtual ~operation();

        void background_image(const array_t &bg);
        const array_t &background_image() const;
        void mask_image(const array_t &mask);
        const array_t &mask_image() const;
        void norm_factor(array_t::value_type f);
        array_t::value_type norm_factor() const;

        //throws an exception if the data does not match the background and mask
        //image.
        void check_data(const array_t &data);

        void operator()(const array_t &data);
};

typedef std::map<string,operation> operator_map_t;


//-----------------------------------------------------------------------------
/*!
\brief find minimum value

Finds the minimum value in the data and plots it so std
*/
void min_operation(const array_t &data);
void max_operation(const array_t &data);
void average_operation(const array_t &data);
void sum_operation(const array_t &data);

