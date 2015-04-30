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
// Created on: Jun 5,2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "config_utils.hpp"

//-----------------------------------------------------------------------------
bool check_help_request(const configuration &config,const string &header)
{
    if(config.value<bool>("help"))
    {
        std::cerr<<header<<std::endl<<std::endl;;
        std::cerr<<config<<std::endl;
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
bool parse_cli_opts(int argc,char **argv,const string &progname,
                    configuration &config)
{
    try
    {
        parse(config,cliargs2vector(argc,argv));
    }
    catch(...)
    {
        std::cerr<<"Wrong or insufficient command line options:"<<std::endl;
        std::cerr<<std::endl;
        std::cerr<<"use "<<progname<<" -h (--help) for more info"<<std::endl;
        return true;
    }

    return false;
}
