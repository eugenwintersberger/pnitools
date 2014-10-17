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

#include "file.hpp"
#include "file_utils.hpp"
#include "exceptions.hpp"

typedef std::vector<string> string_vector;

static const string_vector cbf_extensions = {".cbf"};
static const string_vector tif_extensions = {".tif",".tiff"};
static const string_vector nxs_extensions = {".h5",".nxs",".nx"};
static const string_vector fio_extensions = {".fio"};
static const string_vector spec_extensions = {".spec"};
static const string_vector spe_extensions = {".spe"};

//----------------------------------------------------------------------------
file_type get_file_type(const file &input_file)
{
    if(has_extension(input_file,cbf_extensions))
        return file_type::CBF;
    else if(has_extension(input_file,tif_extensions))
        return file_type::TIF;
    else if(has_extension(input_file,nxs_extensions))
        return file_type::NEXUS;
    else if(has_extension(input_file,fio_extensions))
        return file_type::FIO;
    else if(has_extension(input_file,spec_extensions))
        return file_type::SPEC;
    else if(has_extension(input_file,spe_extensions))
        return file_type::SPE;
    else
        throw file_type_error(EXCEPTION_RECORD,
                "Unkown file type!");

}

