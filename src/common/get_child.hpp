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
#include "is_group.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include "is_valid.hpp"


template<typename VTYPE> 
class get_child_visitor : public boost::static_visitor<
                          typename nxvariant_traits<typename nxvariant_member_type<VTYPE,0>::type>::child_types>
{
    private: 
        string _name;
        string _class;
    public:
        typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
        typedef typename nxvariant_traits<first_member>::child_types result_type;
        DEFINE_NXGROUP(first_member) group_type;
        DEFINE_NXFIELD(first_member) field_type;
        DEFINE_NXATTRIBUTE(first_member) attribute_type;

        get_child_visitor(const string &n,const string &c):
            _name(n),
            _class(c)
        {}
        
        result_type operator()(const group_type &g) const
        {
            //here comes the interesting part
            result_type result; 

            for(auto child: g)
            {
                if(child.object_type() == nxobject_type::NXGROUP)
                    result = group_type(child);
                else if(child.object_type() == nxobject_type::NXFIELD)
                    result = field_type(child);
                else 
                    continue; //maybe one should throw an exception here

                if(is_group(result))
                {
                    //check here for name and type
                    if(_name.empty())
                    {
                        //we only need to check for the class
                        if(is_class(result,_class)) return result;
                    }
                    else 
                    {
                        //we definitly need to check the name
                        if(get_name(result) == _name)
                        {
                            if(_class.empty()) return result;
                            else if(is_class(result,_class))
                                return result;
                        }
                    }
                    continue;
                }
                else if(is_field(result))
                {
                    //check here only for the name
                    if(get_name(result)!=_name) continue;

                    return result;
                }
            }

            //in the worst case we return an invalid object
            return result_type();
        }

        result_type operator()(const field_type &f) const
        {
            throw nxfield_error(EXCEPTION_RECORD,
                    "Fields do not have children!");
        }

        result_type operator()(const attribute_type &a) const
        {
            throw nxattribute_error(EXCEPTION_RECORD,
                    "Attributes do not have children!");

        }
};

template<typename VTYPE> 
typename get_child_visitor<VTYPE>::result_type
get_child(const VTYPE &o,const string &n,const string &c)
{
    return boost::apply_visitor(get_child_visitor<VTYPE>(n,c),o);
}
