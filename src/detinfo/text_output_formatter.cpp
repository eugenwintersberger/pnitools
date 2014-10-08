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

#include "text_output_formatter.hpp"
#include "detector_layout.hpp"

std::ostream &operator<<(std::ostream &stream,const shape_t &shape)
{
    if(shape.empty())
        return stream;
   
    stream<<"(";
    for(auto iter = shape.begin();iter!=shape.end();++iter)
    {
        stream<<*iter;
        if(iter!=shape.end()-1) stream<<",";
    }

    stream<<")";
    return stream;
}

//----------------------------------------------------------------------------
void text_output_formatter::write(std::ostream &stream,
                                  const detector_info &info)
{
    stream<<info.path()<<"  ";
    stream<<"type = "<<string_from_layout(info.layout())<<"  ";
    stream<<"pixel type = "<<info.type_id()<<"  ";

    if(info.layout() != detector_layout::POINT)
        stream<<"frame shape = "<<info.frame_shape();
}
