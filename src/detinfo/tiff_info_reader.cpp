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


#include "tiff_info_reader.hpp"
#include <pni/io/tiff/tiff_reader.hpp>
#include "../common/file.hpp"

using namespace pni::io;
detector_info_list tiff_info_reader::operator()(const file &f) const
{
    detector_info_list list; 
    
    tiff_reader reader(f.path());

    image_info info = reader.info(0);
    list.push_back(detector_info(info.nx(),
                                info.ny(),
                                info.get_channel(0).type_id(),
                                f.path(),
                                reader.nimages()));
    return list;
}
