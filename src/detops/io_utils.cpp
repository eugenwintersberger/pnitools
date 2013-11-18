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
 * Created on: Nov 12, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "io_utils.hpp"

//-----------------------------------------------------------------------------
image_type get_darkfield(const configuration &config)
{
    try
    {
        if(config.has_option("darkfield")) 
            return read_image(config.value<string>("darkfield"));
    }
    catch(file_error &error)
    {
        std::cerr<<"Error reading dark field image!"<<std::endl;
        error.append(EXCEPTION_RECORD);
        throw error;
    }

    return image_type();
}

//-----------------------------------------------------------------------------
image_type get_flatfield(const configuration &config)
{
    try
    {
        if(config.has_option("flatfield"))
            return read_image(config.value<string>("flatfield"));
    }
    catch(file_error &error)
    {
        std::cerr<<"Error reading flatfield image!"<<std::endl;
        error.append(EXCEPTION_RECORD);
        throw error;
    }

    return image_type();
}

//-----------------------------------------------------------------------------
file_list get_input_files(const configuration &config)
{
    try
    {
        //next we have to get the input files
        return file_list_parser::parse<file_list>(
                            config.value<file_name_list>("input-files"));
    }
    catch(cli_option_error &error)
    {
        std::cerr<<"Error reading input files from command line!"<<std::endl;
        error.append(EXCEPTION_RECORD);
        throw error;
    }
    catch(file_error &error)
    {
        std::cerr<<"One of the input files is not a regular file!"<<std::endl;
        error.append(EXCEPTION_RECORD);
        throw error;
    }

    return file_list(); //just to make the compiler happy
}


//------------------------------------------------------------------------------
image_type read_image(const file &infile)
{
    //determine the reader type from the file extension
    string type;
    try
    {
        string extension = infile.extension();
        std::transform(extension.begin(),extension.end(),extension.begin(),
                       std::ptr_fun<int,int>(std::tolower));
        type = type_extension_map[extension];
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Unable to determine file type for file "+infile.path()+ "!");
    }

    try
    {
        if(type == "cbf")
            return read_data(cbf_reader(infile.path()));
        else if(type == "tif")
            return read_data(tiff_reader(infile.path()));
    }
    catch(...)
    {
        throw file_error(EXCEPTION_RECORD,
                "Unable to construct reader for file "+infile.path()+"!");
    }
}

