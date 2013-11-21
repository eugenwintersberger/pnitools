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

#include "plot.hpp"

image_buffer::image_buffer():
    _data(nullptr),
    _nx(0),
    _ny(0)
{}

//-----------------------------------------------------------------------------
image_buffer::~image_buffer()
{
    _deallocate_memory();
}

void image_buffer::shape(size_t nx,size_t ny)
{
    _nx = nx;
    _ny = ny;

    _allocate_memory();
}

//-----------------------------------------------------------------------------
void image_buffer::_allocate_memory()
{
    typedef PLFLT* pointer_type;

    if(_data) _deallocate_memory();

    _data = new pointer_type[_nx];

    for(size_t i=0;i<_nx;++i)
        _data[i] = new PLFLT[_ny];
}

//-----------------------------------------------------------------------------
void image_buffer::_deallocate_memory()
{
    for(size_t i=0;i<_nx;++i)
        delete [] _data[i];;

    delete [] _data;
}
