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
// Created on: Oct 9,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "key_value_output_formatter.hpp"

void key_value_output_formatter::header(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void key_value_output_formatter::footer(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void key_value_output_formatter::detector_header(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void key_value_output_formatter::detector_footer(std::ostream &stream)
{
    stream<<std::endl;
}

//----------------------------------------------------------------------------
void key_value_output_formatter::write(std::ostream &stream,
                                       const detector_info &info)
{
    stream<<"source           = "<<info.path()<<std::endl;
    stream<<"type             = "<<string_from_layout(info.layout());
    stream<<std::endl;

    if(info)
    {
        stream<<"pixel type       = "<<info.type_id()<<std::endl;
        stream<<"number of frames = "<<info.nframes()<<std::endl;
        if(!info.frame_shape().empty())
            stream<<"frame shape      = "<<info.frame_shape()<<std::endl;
    }
    else
    {
        stream<<"target path      = "<<info.target_path()<<std::endl;
    }

}
