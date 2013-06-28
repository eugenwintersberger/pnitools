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
 * Created on: Jun 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxvariant_traits.hpp"

template<typename OTYPE> 
class is_valid_visitor :: public boost::static_visitor<bool>
{
    public:
        DEFINE_NXGROUP(OTYPE) group_type;
        DEFINE_NXFIELD(OTYPE) field_type;
        DEFINE_NXATTRIBUTE(OTYPE) attribute_type;
        
        bool operator()(const group_type &g)
        {
            return g.is_valid();
        }

        bool operator()(const field_type &f)
        {
            return g.is_valid();
        }

        bool operator()(const attribute_type &a)
        {
            return a.is_valid();
        }
};

template<typename OTYPE> 
bool is_valid(const typename nxvariant_traits<OTYPE>::object_types &o)
{
    return boost::apply_visitor(is_valid_visitor<OTYPE>(),o);
}

template<typename OTYPE> 
bool is_valid(const typename nxvariant_traits<OTYPE>::io_types &o)
{
    return boost::apply_visitor(is_valid_visitor<OTYPE>(),o);
}
