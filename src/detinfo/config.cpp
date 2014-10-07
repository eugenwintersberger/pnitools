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

#include "types.hpp"
#include "config.hpp"

configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<bool>("verbose","v","be verbose",false));
    config.add_option(config_option<bool>("full-path","",
                "show the full path on output",false));
    config.add_option(config_option<bool>("nx","x",
                "show number of points along the first dimension",false));
    config.add_option(config_option<bool>("ny","y",
                "show number of points along the second dimension",false));
    config.add_option(config_option<bool>("ntot","n",
                "show the total number of points",false));
    config.add_option(config_option<bool>("dtype","d",
                "show the data type",false));
    config.add_option(config_option<bool>("list-files","l",
                "just list the files found",false));
    config.add_option(config_option<bool>("frames","f",
                "number of frames in the file",false));
    config.add_argument(config_argument<string_list>("input-files",-1,
                        string_list{"-"}));

    return config;
}
