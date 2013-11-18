/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Oct 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "detops.hpp"

configuration create_config()
{
    configuration config;
    
    config.add_option(config_option<bool>("help","h","show help",false));
    config.add_option(config_option<bool>("verbose","v",
                "show verbose output",false));
    config.add_option(config_option<bool>("print-files","p",
                "print filenames along with output",false));
    config.add_option(config_option<string>("command","c",
                "which operation to perform","sum"));
    config.add_option(config_option<string>("roi","r",
                "set region of interest"));
    config.add_option(config_option<string>("darkfield","d",
                "name of the darkfield file"));
    config.add_option(config_option<string>("flatfield","f",
                "name of a flatfield file"));
    config.add_argument(config_argument<std::vector<string>>("input-files",-1));



    return config;


}
