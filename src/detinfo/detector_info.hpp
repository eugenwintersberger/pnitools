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

#include "detector_layout.hpp"

using namespace pni::core;


//!
//! \brief class with single detector information
//! 
//! This class provides all the information required for a single detector. 
//!
class detector_info
{
    private:
        //! typ ID for the pixel
        type_id_t _tid;
        //! path to the detector file
        string _file_path;
        //! number of frames stored in the file
        size_t _nframes;
        //! shape of a single frame
        shape_t _frame_shape;
        //! the layout of the detector
        detector_layout _layout;
        
    public:
        explicit detector_info(const shape_t &frame_shape,
                               type_id_t pixel_type,
                               const string &file_path,
                               size_t nframes,
                               detector_layout layout);
    
        shape_t frame_shape() const;

        size_t nframes() const;

        string path() const;

        type_id_t type_id() const;

        detector_layout layout() const;
};

typedef std::vector<detector_info> detector_info_list;
                               


        

