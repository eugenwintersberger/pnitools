//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "roi.hpp"
#include <pni/io/parsers.hpp>

using namespace pni::core;
using namespace pni::io;

size_t size(const roi_type &roi)
{
    size_t result=1;

    for(auto s: roi) 
        result *= pni::core::size(s);

    return result;
}

//----------------------------------------------------------------------------
size_t rank(const roi_type &roi)
{
    return roi.size();
}

//----------------------------------------------------------------------------
std::istream &operator>>(std::istream &stream,roi_type &roi)
{
    parser<string::const_iterator,roi_type> p(','); 
    
    string buffer; 
    stream>>buffer;
    roi = p(buffer);

    return stream;

}
