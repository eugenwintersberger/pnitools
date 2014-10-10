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
// Created on: Oct 10,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "xml_output_formatter.hpp"

const string xml_output_formatter::detector_indent = "\t";
const string xml_output_formatter::data_indent = "\t\t";


void xml_output_formatter::header(std::ostream &stream)
{
    stream<<"<?xml version=\"1.0\"?>"<<std::endl;
    stream<<"<detinfo>"<<std::endl;
}

//----------------------------------------------------------------------------
void xml_output_formatter::footer(std::ostream &stream)
{
    stream<<"</detinfo>"<<std::endl;
}

//----------------------------------------------------------------------------
void xml_output_formatter::detector_header(std::ostream &stream)
{
    stream<<detector_indent<<"<detector>"<<std::endl;
}

//----------------------------------------------------------------------------
void xml_output_formatter::detector_footer(std::ostream &stream)
{
    stream<<detector_indent<<"</detector>"<<std::endl;
}

//----------------------------------------------------------------------------
void xml_output_formatter::write(std::ostream &stream,
                                 const detector_info &info)
{
    stream<<data_indent<<"<source>";
    stream<<info.path();
    stream<<"</source>"<<std::endl;

    stream<<data_indent<<"<type>";
    stream<<string_from_layout(info.layout());
    stream<<"</type>"<<std::endl;

    stream<<data_indent<<"<pixeltype>"<<info.type_id()<<"</pixel>"<<std::endl;

    stream<<data_indent<<"<frames>"<<info.nframes()<<"</frames>"<<std::endl;

    stream<<data_indent<<"<frameshape>";
    stream<<info.frame_shape()<<"</frameshape>"<<std::endl;
}
