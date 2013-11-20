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
 * Created on: Nov 14, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "image_processor.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif


image_processor::image_processor():
    _op_stack()
{}

//-----------------------------------------------------------------------------
image_type image_processor::operator()(const image_type &input) 
{
    std::reference_wrapper<const image_type> image = std::cref(input); //the initial image is user input
#ifdef NOFOREACH
    BOOST_FOREACH(auto &op,_op_stack)
#else
    for(auto &op: _op_stack)
#endif
    {
        op->execute(input);
        image = std::cref(op->result()); //set image to the result of the current 
                             //operation
    }

    return image; //copy the final result out of the function
}

//-----------------------------------------------------------------------------
void image_processor::push_back(op_ptr_type op)
{
    _op_stack.push_back(std::move(op));
}


//-----------------------------------------------------------------------------
size_t image_processor::size() const
{
    return _op_stack.size();
}

