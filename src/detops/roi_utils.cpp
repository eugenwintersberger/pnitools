//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 12, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "roi_utils.hpp"

roi_type get_roi_from_string(const string &s)
{
    typedef std::vector<slice> slice_vector;
    typedef parser<slice_vector> parser_type;
    roi_type roi;

    parser_type p(',');

    auto rois = p(s);

    return roi_type{rois[0],rois[1]};
}

//-----------------------------------------------------------------------------
roi_stack get_roi_stack(const configuration &config)
{
    roi_stack stack;
    if(config.has_option("roi"))
        stack.push_back(get_roi_from_string(config.value<string>("roi")));

    return stack;

}
