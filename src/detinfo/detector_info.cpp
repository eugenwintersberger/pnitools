//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: Oct 7,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "detector_info.hpp"

//-----------------------------------------------------------------------------
detector_info::detector_info(const shape_t &frame_shape,
                             type_id_t pixel_type,
                             const string &file_path,
                             size_t nframes,
                             detector_layout layout):
    _frame_shape(frame_shape),
    _tid(pixel_type),
    _file_path(file_path),
    _nframes(nframes),
    _layout(layout),
    _resolvable(true),
    _target_path{}
{}

//-----------------------------------------------------------------------------
detector_info::detector_info(const string &file_path,
                             detector_layout layout,
                             const string &target_path):
    _frame_shape{},
    _tid{},
    _file_path(file_path),
    _nframes(0),
    _layout(layout),
    _resolvable{false},
    _target_path(target_path)
{}

//----------------------------------------------------------------------------
shape_t detector_info::frame_shape() const
{
    return _frame_shape;
}

//----------------------------------------------------------------------------
size_t detector_info::nframes() const
{
    return _nframes;
}

//----------------------------------------------------------------------------
string detector_info::path() const
{
    return _file_path;
}

//----------------------------------------------------------------------------
type_id_t detector_info::type_id() const
{
    return _tid;
}

//----------------------------------------------------------------------------
detector_layout detector_info::layout() const
{
    return _layout;
}

//----------------------------------------------------------------------------
string detector_info::target_path() const
{
    return _target_path; 
}
