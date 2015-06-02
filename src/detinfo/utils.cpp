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

#include "utils.hpp"

#include "cbf_info_reader.hpp"
#include "tiff_info_reader.hpp"
#include "nexus_info_reader.hpp"
#include "formatter_factory.hpp"
#include "../common/file_type.hpp"
#include "../common/file_list_parser.hpp"


//----------------------------------------------------------------------------
detector_info_list get_info(const file &f)
{
    typedef std::unique_ptr<detector_info_reader> reader_pointer;
    
    reader_pointer reader;
    switch(get_file_type(f))
    {
        case file_type::CBF_FILE:
            reader = reader_pointer(new cbf_info_reader()); break;
        case file_type::TIFF_FILE:
            reader = reader_pointer(new tiff_info_reader()); break;
        case file_type::NEXUS_FILE:
            reader = reader_pointer(new nexus_info_reader()); break;
        default:
            throw file_error(EXCEPTION_RECORD, "Unkonw file type");
    }

    return (*reader)(f);
}

//----------------------------------------------------------------------------
output_formatter *get_output_formatter(const configuration &config)
{
    try
    {
        auto format = config.value<string>("format");
        return formatter_factory::output(format);
    }
    catch(value_error &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Unknown error during output formatter creation!";
        std::cerr<<std::endl;
        std::exit(1);
    }
}

//---------------------------------------------------------------------------
file_list get_input_files(const configuration &config)
{
    //retrieve list of input files passed by the user
    try
    {
        auto name_list = config.value<string_list>("input-files");
        return file_list_parser::parse<file_list>(name_list);
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Error while creating input file list!"<<std::endl;
        std::exit(1);
    }
}
