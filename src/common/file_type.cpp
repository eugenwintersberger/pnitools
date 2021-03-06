//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 22, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "file_type.hpp"

using namespace pni::core;
namespace fs = boost::filesystem;

static const unsigned char TIFF_LE[] = {0x49,0x49,0x2A,0x00};
static const unsigned char TIFF_BE[] = {0x4D,0x4D,0x00,0x2A};
static const unsigned char HDF5[] = {0x89,0x48,0x44,0x46,
                               0x0d,0x0a,0x1a,0x0a};

static const size_t read_buf_size = 8;

std::ostream &operator<<(std::ostream &stream,const file_type &type)
{
    switch(type)
    {
        case file_type::UNKNOWN:
            return stream<<"UNKNOWN";
        case file_type::NEXUS_FILE:
            return stream<<"NEXUS";
        case file_type::TIFF_FILE:
            return stream<<"TIFF";
        case file_type::CBF_FILE:
            return stream<<"CBF";
        case file_type::SPEC_FILE:
            return stream<<"SPEC";
        case file_type::FIO_FILE:
            return stream<<"FIO";
    }
}


//----------------------------------------------------------------------------
bool is_tiff(unsigned char *buffer)
{
    return std::equal(TIFF_LE,TIFF_LE+4,buffer) ||
           std::equal(TIFF_BE,TIFF_BE+4,buffer);
}

//----------------------------------------------------------------------------
bool is_hdf5(unsigned char *buffer)
{
    return std::equal(HDF5,HDF5+4,buffer);
}

//----------------------------------------------------------------------------
file_type get_file_type(const pni::core::string &fname)
{
    unsigned char buffer[read_buf_size];

    std::ifstream file_stream(fname);
    file_stream.read(reinterpret_cast<char*>(buffer),8);

    if(is_tiff(buffer))     
        return file_type::TIFF_FILE;
    else if(is_hdf5(buffer))
        return file_type::NEXUS_FILE;
    else 
    {
        fs::path f(fname);
        string extension = f.extension().string();
        boost::to_lower(extension);
        //we are now done with meagic bytes and go to file extensions
        if(extension == ".fio") return file_type::FIO_FILE;
        else if(extension == ".spec") return file_type::SPEC_FILE;
        else if(extension == ".cbf") return file_type::CBF_FILE;
        else
            return file_type::UNKNOWN;
    } 
    return file_type::UNKNOWN;
}

//----------------------------------------------------------------------------
file_type get_file_type(const file &f)
{
    return get_file_type(f.path());
}
