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
// Created on: May 28, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/io/parsers.hpp>
#include "utils.hpp"

using namespace pni::core;
using namespace pni::io;

std::istream &operator>>(std::istream &stream,slice &s)
{
    typedef parser<string::const_iterator,slice> parser_type;

    parser_type p;
    string data;
    stream>>data;
    s = p(data);

    return stream;
}

//-----------------------------------------------------------------------------
configuration create_global_config()
{
    configuration config;

    //----------------setting up the program options---------------------------
    //these options do not show up in the help text
    config.add_argument(config_argument<string>("command",1));
    config.add_argument(config_argument<string>("input",2));

    //-------------------------------------------------------------------------
    //global options valid for all commands
    config.add_option(config_option<bool>("help","h","show help text",false));
    config.add_option(config_option<bool>("verbose","v","show verbose output",
                                          false));
    config.add_option(config_option<bool>(
                "header","","write headers before output",false));

    config.add_option(config_option<string>("channels","c",
                "name of the column with bin center values"));
    config.add_option(config_option<string>("bins","b",
                "name of the column with the center values"));
    config.add_option(config_option<string>("mca","m",
                "name of the MCA columns"));
    config.add_option(config_option<size_t>("auto-index-offset","",
                "offset for automatic channel index",size_t(0)));
    
    config.add_option(config_option<size_t>("mca-size","s",
                "number of channels of a single MCA spectrum",size_t(0)));

    config.add_option(config_option<slice>("roi","r",
                "ROI for the input data"));

    return config;
}

//-----------------------------------------------------------------------------
void apply_roi(operation::data_range &range,const slice &roi)
{
    range.second = range.first;
    std::advance(range.first,roi.first());
    std::advance(range.second,roi.last());
}

//------------------------------------------------------------------------------
bool check_argument_count(int argc)
{
    if(argc<2)
    {
        std::cerr<<usage_string<<std::endl;
        std::cerr<<"\nuse mcaops -h for more information"<<std::endl;
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
bool manage_help_request(const configuration &c)
{
    if(c.value<bool>("help"))
    {
        std::cerr<<usage_string<<std::endl<<std::endl;
        std::cerr<<command_string<<std::endl;
        std::cerr<<c<<std::endl;
        return true;
    }

    return false;
}
