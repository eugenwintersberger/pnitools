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
 * Created on: Nov 21, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>
#include <pni/core/exceptions.hpp>
#include <boost/lexical_cast.hpp>
#include <plplot/plstream.h>
#include <cmath>

using namespace pni::core;

/*!
\brief buffer holding image data

For images plplot requires a special buffer in old C-style. This class
encapsulates this buffer and thus actas as a guard for the raw C pointers.
*/
class image_buffer
{
    private:
        PLFLT **_data;  //!< image data
        size_t _nx;  //!< number of columns
        size_t _ny;  //!< number of rows

        void _allocate_memory();
        void _deallocate_memory();
    public:
        image_buffer();
        ~image_buffer();
        void shape(size_t nx,size_t ny);

        template<typename ATYPE> void data(const ATYPE &a);
        const PLFLT **data() const
        {
            return (const PLFLT**)_data;
        }
};

template<typename ATYPE> void image_buffer::data(const ATYPE &a)
{
    //--------------check the total size---------------------------------------
    if(_nx*_ny != a.size())
        throw size_mismatch_error(EXCEPTION_RECORD,
                "Total image size ("+boost::lexical_cast<string>(_nx*_ny)
                +") does not match total data size ("+
                boost::lexical_cast<string>(a.size())+")!");

    //---------------check the rank of the array-------------------------------
    if(a.rank() != 2)
        throw shape_mismatch_error(EXCEPTION_RECORD,
                "Input array is not of rank 2!");

    //-----------------check shape---------------------------------------------
    auto shape = a.template shape<shape_t>();
    if((shape[0] != _nx) || (shape[1] != _ny))
        throw shape_mismatch_error(EXCEPTION_RECORD,
                "Shape of input array ("+
                boost::lexical_cast<string>(shape[0])+","+
                boost::lexical_cast<string>(shape[1])+") does not match "+
                "image shape ("+
                boost::lexical_cast<string>(_nx)+","+
                boost::lexical_cast<string>(_ny)+")!");

    //copy data
    for(size_t i=0;i<_nx;++i)
        for(size_t j=0;j<_ny;++j)
            _data[i][j] = std::log10(a(i,j));
}

/*!
\brief create image buffer from array

Create an image buffer from an array. 
*/
template<typename ATYPE> image_buffer image_buffer_from_array(const ATYPE &a)
{
    auto shape = a.template shape<shape_t>();
    image_buffer buffer;
    buffer.shape(shape[0],shape[1]);
    buffer.data(a);

    return buffer;
}


