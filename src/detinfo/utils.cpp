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

#include "utils.hpp"
#include "../common/file_utils.hpp"

#include "cbf_info_reader.hpp"
#include "tiff_info_reader.hpp"
#include "nexus_info_reader.hpp"

const static string_list cbf_exts = {".cbf"};
const static string_list tif_exts = {".tif",".tiff"};
const static string_list nx_exts = {".nxs",".nx"};

//----------------------------------------------------------------------------
file_type get_file_type(const file &f)
{
    if(has_extension(f,cbf_exts))
        return file_type::CBF;
    else if(has_extension(f,tif_exts))
        return file_type::TIFF;
    else if(has_extension(f,nx_exts))
        return file_type::NEXUS;
    else
        throw file_error(EXCEPTION_RECORD,
                "Unknown input file type!");

}

//----------------------------------------------------------------------------
detector_info_list get_info(const file &f)
{
    typedef std::unique_ptr<detector_info_reader> reader_pointer;

    file_type type = get_file_type(f);
    
    reader_pointer reader;
    if(type == file_type::CBF)
        reader = reader_pointer(new cbf_info_reader());
    else if(type == file_type::TIFF)
        reader = reader_pointer(new tiff_info_reader());
    else if(type == file_type::NEXUS)
        reader == reader_pointer(new nexus_info_reader());

    return (*reader)(f);
}
