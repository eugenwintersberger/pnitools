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
#include "fio_provider.hpp"

using namespace pni::core;

data_provider::pointer_type 
data_provider_factory::create_stdin_provider(const configuration &c)
{
    if(c.value<bool>("verbose"))
    {
        std::cerr<<"Creating input provider for standard input!";
        std::cerr<<std::endl;
    }

    //------------------------------------------------------------------------
    // these options have default value which we can use
    //------------------------------------------------------------------------
    auto mca_size = c.value<size_t>("mca-size");
    auto index_offset = c.value<size_t>("auto-index-offset");

    //------------------------------------------------------------------------
    // construct the provider
    //------------------------------------------------------------------------
    return pointer_type(new
            stdin_provider(mca_size,index_generator(index_offset)));
}

//----------------------------------------------------------------------------
data_provider::pointer_type 
data_provider_factory::create_fio_provider(const configuration &c,
                                           const filename_vector &filenames)
{
    if(c.value<bool>("verbose"))
        std::cerr<<"Creating input provider for a FIO file!"<<std::endl;

    //------------------------------------------------------------------------
    // get the column name for the MCA data in the file
    //------------------------------------------------------------------------
    string mca_col_name;
    if(c.has_option("mca"))
        mca_col_name = c.value<string>("mca");
    else
        throw cli_error(EXCEPTION_RECORD,
                "For FIO files the -m (--mca) option has to be used!");

    //------------------------------------------------------------------------
    // get the channel/bin-center column name (optional)
    //------------------------------------------------------------------------
    string channel_col_name;
    if(c.has_option("channels"))
        channel_col_name = c.value<string>("channels");
    else if(c.has_option("bins"))
        channel_col_name = c.value<string>("bins");

    //------------------------------------------------------------------------
    // get the channel offset
    //------------------------------------------------------------------------
    auto coffset = c.value<size_t>("auto-index-offset");

    //------------------------------------------------------------------------
    // construct the provider
    //------------------------------------------------------------------------

    return pointer_type(new fio_provider(filenames.front(),
                                         mca_col_name,channel_col_name,
                                         coffset));

}

//----------------------------------------------------------------------------
data_provider::pointer_type 
data_provider_factory::create(const configuration &config)
{
    typedef data_provider::pointer_type pointer_type;
    if(config.has_option("input-files"))
    {
        auto file_names = config.value<std::vector<string>>("input-files");
        string file_name = file_names.front();
        switch(get_file_type(file_names.front()))
        {
            case file_type::NEXUS_FILE:
                std::cerr<<"Nexus files"<<std::endl;
            case file_type::FIO_FILE:
                return create_fio_provider(config,file_names);
            default:
                return pointer_type();
        }
    }
    else
    {
        return create_stdin_provider(config);
    }

}
