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
 * Created on: Nov 12, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include <vector>
#include "types.hpp"
#include "image_op_base.hpp"


class image_processor
{
    public:
        typedef std::unique_ptr<image_op_base> op_ptr_type;
        typedef std::vector<op_ptr_type> op_stack_type;
    private:

        op_stack_type _op_stack; //!< stack of operations

    public:
        image_processor();

        image_type operator()(const image_type &image) ;

        void push_back(op_ptr_type op);
        
        op_stack_type::reference front() 
        {
            return _op_stack.front();
        }

        op_stack_type::const_reference front() const
        {
            return _op_stack.front();
        }

        op_stack_type::reference back() 
        {
            return  _op_stack.back();
        }

        op_stack_type::const_reference back() const
        {
            return _op_stack.back();
        }

        size_t size() const;



};
