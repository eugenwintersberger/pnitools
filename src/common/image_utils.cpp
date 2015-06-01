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
// Created on: Oct 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "image_utils.hpp"
#include "file_utils.hpp"
#include "exceptions.hpp"

#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/tiff/tiff_reader.hpp>

using namespace pni::core;
using namespace pni::io;

//----------------------------------------------------------------------------
image_reader_ptr get_image_reader(const file &image_file)
{
    file_type type = get_file_type(image_file);

    if(type == file_type::CBF)
        return image_reader_ptr(new cbf_reader(image_file.path()));
    else if(type == file_type::TIF)
        return image_reader_ptr(new tiff_reader(image_file.path()));
    else
        throw file_type_error(EXCEPTION_RECORD,
                "Unkown image format!");
}

//----------------------------------------------------------------------------
image_info get_image_info(const file &image_file)
{
    image_reader_ptr reader(get_image_reader(image_file));

    return reader->info(0);
}
