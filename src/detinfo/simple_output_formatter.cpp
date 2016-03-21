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

#include "simple_output_formatter.hpp"
#include "detector_layout.hpp"


//----------------------------------------------------------------------------
void simple_output_formatter::header(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void simple_output_formatter::footer(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void simple_output_formatter::detector_header(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void simple_output_formatter::detector_footer(std::ostream &stream)
{}

//----------------------------------------------------------------------------
void simple_output_formatter::write(std::ostream &stream,
                                  const detector_info &info)
{
    stream<<info.path()<<"  ";
    stream<<"type = "<<string_from_layout(info.layout())<<"  ";

    if(info)
    {
        stream<<"pixel type = "<<info.type_id()<<"  ";
        stream<<"frames = "<<info.nframes()<<" ";

        if(info.layout() != detector_layout::POINT)
            stream<<"frame shape = "<<info.frame_shape();
    }
    else
    {
        stream<<"target = "<<info.target_path();
    }

    stream<<std::endl;
}
