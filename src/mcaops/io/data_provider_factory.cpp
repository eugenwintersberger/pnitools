//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// libpniutils is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
// Created on: May 12,2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "../../common/file_type.hpp"
#include "data_provider_factory.hpp"
#include "stdin_provider.hpp"

using namespace pni::core;

data_provider::pointer_type data_provider_factory::create_stdin_provider(
        const configuration &c)
{
    if(c.value<bool>("verbose"))
    {
        std::cerr<<"Creating input provider for standard input!";
        std::cerr<<std::endl;
    }

    auto mca_size = c.value<size_t>("mca-size");
    auto index_offset = c.value<size_t>("auto-index-offset");
    return pointer_type(new
            stdin_provider(mca_size,index_generator(index_offset)));
}

//----------------------------------------------------------------------------
data_provider::pointer_type data_provider_factory::create(const configuration
        &config)
{
    typedef data_provider::pointer_type pointer_type;
    if(config.has_option("input-files"))
    {
        if(config.value<bool>("verbose"))
        {
            std::cerr<<"Creating file data provider for";
        }

        auto file_names = config.value<std::vector<string>>("input-files");
        switch(get_file_type(file_names.front()))
        {
            case file_type::NEXUS_FILE:
                std::cerr<<"Nexus files"<<std::endl;
            case file_type::FIO_FILE:
                std::cerr<<"FIO files"<<std::endl;
            default:
                return pointer_type();
        }
    }
    else
    {
        return create_stdin_provider(config);
    }

}
