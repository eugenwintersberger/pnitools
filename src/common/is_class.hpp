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
 * Created on: Jul 1, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxvariant_traits.hpp"

template<typename VTYPE> 
class is_class_visitor : public boost::static_visitor<string>
{
    private:
        string _class;
    public:
        typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
        typedef bool result_type;
        DEFINE_NXGROUP(first_member) group_type;
        DEFINE_NXFIELD(first_member) field_type;
        DEFINE_NXATTRIBUTE(first_member) attribute_type;

        is_class_visitor(const string &s):_class(s) {}
        
        result_type operator()(const group_type &g) const
        {
            string buffer;
            if(g.has_attr("NX_class"))
                g.attr("NX_class").read(buffer);
            else
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Group "+g.path()+" has no class attribute!");

            return buffer==_class;

        }

        result_type operator()(const field_type &f) const
        {
            throw nxfield_error(EXCEPTION_RECORD,
                    "Fields do not have a class!");
            return result_type();
        }

        result_type operator()(const attribute_type &a) const
        {
            throw nxattribute_error(EXCEPTION_RECORD,
                    "Attributes do not have a class!");
            return result_type();
        }
};

template<typename VTYPE> 
typename is_class_visitor<VTYPE>::result_type 
is_class(const VTYPE &o,const string &c)
{
    return boost::apply_visitor(is_class_visitor<VTYPE>(c),o);
}
