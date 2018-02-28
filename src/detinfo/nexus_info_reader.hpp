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

#include "detector_info_reader.hpp"
#include <pni/io/nexus.hpp>
#include "../common/string_utils.hpp"

using namespace pni::io;

class nexus_info_reader : public detector_info_reader
{
    public:
        using detector_list = nexus::GroupList;
    private:
        //--------------------------------------------------------------------
        //!
        //! \brief get info from NXdetector
        //!
        //! Construct an detector_info object form an instance of NXdetector. 
        //!
        //! \throws key_error if a required field does not exist
        //!
        //! \param d group instance of type NXdetector
        //! \return detector_info instance
        //!
        static detector_info info_from_nxdetector(const hdf5::node::Group &d);

        static detector_layout get_detector_layout(const hdf5::node::Group &detector_group);

    public:
        virtual detector_info_list operator()(const file &f) const;
};




