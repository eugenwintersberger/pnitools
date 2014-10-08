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
// Created on: Oct 8,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "detector_layout.hpp"

detector_layout layout_from_string(const string &s)
{
    if(s=="point")
        return detector_layout::POINT;
    else if(s=="linear")
        return detector_layout::LINEAR;
    else if(s=="area")
        return detector_layout::AREA;
    else
        throw value_error(EXCEPTION_RECORD,
                "String does not encode a detector layout!");
}

//----------------------------------------------------------------------------
string string_from_layout(const detector_layout &layout)
{
    if(layout == detector_layout::POINT)
        return "point";
    else if(layout == detector_layout::LINEAR)
        return "linear";
    else if(layout == detector_layout::AREA)
        return "area";
    else
        throw value_error(EXCEPTION_RECORD,
                "The detector layout does not have a string representation!");
}

//----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &stream,const detector_layout &layout)
{
    stream<<string_from_layout(layout);
    return stream;
}

//----------------------------------------------------------------------------
std::istream &operator<<(std::istream &stream,detector_layout &layout)
{
    string input;
    stream>>input;
    layout = layout_from_string(input);
    return stream;
}
