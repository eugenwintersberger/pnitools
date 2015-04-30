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
    typedef string::const_iterator iterator_type;
    typedef parser<iterator_type,slice> parser_type;
    roi_type roi;

    parser_type parser;

    auto sep_iter = std::find(s.begin(),s.end(),',');
    if(sep_iter == s.end())
        throw parser_error(EXCEPTION_RECORD,
                "A ROI should use a ',' to separate dimensions!");

    try
    {
        auto first = s.begin();
        auto last  = s.end();
        roi.first = parser(string(first,sep_iter));
        roi.second = parser(string(++sep_iter,last));
    }
    catch(...)
    {
        throw parser_error(EXCEPTION_RECORD,
                "Error parsing ROI string ("+s+")!");
    }

    return roi;
}

//-----------------------------------------------------------------------------
roi_stack get_roi_stack(const configuration &config)
{
    roi_stack stack;
    if(config.has_option("roi"))
        stack.push_back(get_roi_from_string(config.value<string>("roi")));

    return stack;

}
