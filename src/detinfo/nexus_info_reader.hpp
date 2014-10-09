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
#include "../common/string_utils.hpp"

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
        static detector_info info_from_nxdetector(const h5::nxgroup &d);

        //--------------------------------------------------------------------
        //!
        //! \brief get path of object
        //! 
        //! Return the path to the data holding object. 
        template<typename OTYPE>
        static string get_detector_path(const OTYPE &o);

        template<typename OTYPE>
        static detector_layout get_detector_layout(const OTYPE &o);

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

//----------------------------------------------------------------------------
template<typename OTYPE>
string nexus_info_reader::get_detector_path(const OTYPE &o)
{
    nxpath path = nxpath::from_string(get_path(o));
    path.filename(o.filename());

    return nxpath::to_string(path);
}

//----------------------------------------------------------------------------
template<typename OTYPE>
detector_layout nexus_info_reader::get_detector_layout(const OTYPE &o)
{
    string layout;
    h5::nxfield(o["layout"]).read(layout);
    layout = trim(layout);

    return layout_from_string(layout);
}

