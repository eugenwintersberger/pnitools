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
#pragma once

#include <vector>
#include <pni/core/types.hpp>

using namespace pni::core;

//!
//! \brief class with single detector information
//! 
//! This class provides all the information required for a single detector. 
//!
class detector_info
{
    private:
        //! number of pixels in first dimension
        size_t _nx;
        //! number of pixels in second dimension
        size_t _ny;
        //! typ ID for the pixel
        type_id_t _tid;
        //! path to the detector file
        string _file_path;
        //! number of frames stored in the file
        size_t _nframes;
    public:
        explicit detector_info(size_t nx,size_t ny,type_id_t tid,
                               const string &file_path,
                               size_t nframes);

        size_t nx() const;

        size_t ny() const;

        size_t nframes() const;

        string path() const;

        type_id_t type_id() const;
};

typedef std::vector<detector_info> detector_info_list;
                               


        

