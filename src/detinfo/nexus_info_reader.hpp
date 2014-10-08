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
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/flat_group.hpp>

using namespace pni::io::nx;

class nexus_info_reader : public detector_info_reader
{
    public:
        typedef std::vector<h5::nxgroup> detector_list;
    private:

        //--------------------------------------------------------------------
        template<typename PTYPE>
        static detector_list get_detectors(const PTYPE &parent);

        //--------------------------------------------------------------------
        static detector_info info_from_nxdetector(const h5::nxgroup &d);

    public:
        virtual detector_info_list operator()(const file &f) const;
};

//----------------------------------------------------------------------------
template<typename PTYPE>
nexus_info_reader::detector_list 
nexus_info_reader::get_detectors(const PTYPE &parent)
{
    detector_list detectors;
    std::copy_if(parent.begin(),parent.end(),
                 std::back_inserter(detectors),
                 [](const h5::nxobject &o) 
                 { 
                    return is_group(o) && is_class(o,"NXdetector");
                 }
                );

    return detectors;
}

