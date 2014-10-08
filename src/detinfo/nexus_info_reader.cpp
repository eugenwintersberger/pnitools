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


#include "nexus_info_reader.hpp"
#include "../common/file.hpp"
#include "../common/string_utils.hpp"


detector_info_list nexus_info_reader::operator()(const file &f) const
{
    detector_info_list list; 

    //select all detecotor instances
    h5::nxfile input = h5::nxfile::open_file(f.path());

    detector_list detectors = get_detectors(make_flat(input.root()));

    for(auto detector: detectors)
        list.push_back(info_from_nxdetector(detector));
    
    return list;
}

//----------------------------------------------------------------------------
detector_info nexus_info_reader::info_from_nxdetector(const h5::nxgroup &d)
{
    h5::nxfield data = d["data"];

    auto shape = data.shape<shape_t>();

    string layout;
    h5::nxfield(d["layout"]).read(layout);
    layout = trim(layout);

    if(layout == "point")
        return detector_info(shape_t(),data.type_id(),
                             get_path(data),
                             shape[0],
                             layout_from_string(layout));
    else if(layout == "linear")
        return detector_info(shape_t({shape[1]}),
                             data.type_id(),
                             get_path(data),
                             shape[0],
                             layout_from_string(layout));
    else if(layout == "area")
        return detector_info(shape_t{shape[1],shape[2]},data.type_id(),
                             get_path(data),
                             shape[0],
                             layout_from_string(layout));
    else
        throw type_error(EXCEPTION_RECORD,"Unknown detector layout!");
}
