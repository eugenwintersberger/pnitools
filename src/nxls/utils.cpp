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
// Created on: Oct 13,2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/exceptions.hpp>
#include "utils.hpp"

nxpath get_path(const configuration &config)
{
    try
    {
        return nxpath::from_string(config.value<string>("nxpath"));
    }
    catch(pni::io::parser_error &error)
    {
        std::cerr<<error<<std::endl;
        std::cerr<<std::endl;
        std::cerr<<"Check if the :// is appended to the filename if you want"
                 <<" to show the content from the root group!"<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Unknown error during path parsing - aborting program!";
        std::cerr<<std::endl;
        std::exit(1);
    }
}

//----------------------------------------------------------------------------
h5::nxfile get_file(const nxpath &path)
{
    if(path.filename().empty())
    {
        std::cerr<<"Please provide a filename!"<<std::endl;
        std::exit(1);
    }

    try
    {
        return h5::nxfile::open_file(path.filename(),true);
    }
    catch(...)
    {
        std::cerr<<"Error opening Nexus file!"<<std::endl;
        std::exit(1);
    }
}

//----------------------------------------------------------------------------
h5::nxobject get_root(const h5::nxfile &file,const nxpath &path)
{
    try
    {
        return get_object(file.root(),path);
    }
    catch(pni::core::key_error &error)
    {
        std::cerr<<error<<std::endl;
        std::cerr<<"The path entered does not exist!"<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Unkonwn error when retrieving the root object!"<<std::endl;
        std::exit(1);
    }
}
