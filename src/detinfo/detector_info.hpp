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

        bool _resolvable;
        string _target_path;

        
    public:
        //!
        //! \brief constructor 
        //!
        //! Use this constructor to build an instance of detector_info 
        //! if link to the detector data can be resolved.
        //!
        //! \param frame_shape the shape of a single frame
        //! \param pixel_type the data type of an individual pixel
        //! \param file_path the path to the detetor object within the file
        //! \param nframes number of frames stored in the file
        //! \param layout the layout of the detector
        //!
        explicit detector_info(const shape_t &frame_shape,
                               type_id_t pixel_type,
                               const string &file_path,
                               size_t nframes,
                               detector_layout layout);

        //!
        //! \brief constructor
        //!
        //! Use this constructor to build an instance of detector_info in 
        //! situations where the link to the detector data could not be
        //! resolved.
        //! 
        //! \param file_path path to the detector link
        //! \param layout the layout of the detector
        //! \param target_path path to the original target where the data
        //!                    should be stored
        //!
        explicit detector_info(const string &file_path,
                               detector_layout layout,
                               const string &target_path);
    
        shape_t frame_shape() const;

        size_t nframes() const;

        string path() const;

        type_id_t type_id() const;

        detector_layout layout() const;

        string target_path() const;
        
        explicit operator bool() const { return _resolvable; }
};

typedef std::vector<detector_info> detector_info_list;
                               


        

