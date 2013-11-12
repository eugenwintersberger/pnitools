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
#include "io_utils.hpp"



//list of file names
typedef std::vector<string> file_name_list;
//list of file objects
typedef std::vector<file> file_list;

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


//-----------------------------------------------------------------------------
int main(int argc, char **argv) 
{

    configuration config = create_config();

    if(parse_cli_opts(argc,argv,"detops",config)) return 1;

    if(check_help_request(config,"")) return 1;

    //=========================basic input reading=============================
    //we try to do as much as possible before reading the list of input files.
    //As this list can be long and thus checking the files might take a while we
    //do not want to recognize right after this expensive job that we hat to
    //throw an exception due to some simple operation

    //select the command
    
    //===============read darkfield and flatfield images========================
    try
    {
        image_type dark_image = get_darkfield(config);
        image_type flat_image = get_flatfield(config);


        //setup rois (if there are any)
        if(config.has_option("roi"))
        {
            
        }

   
        //=================now we read the fetch the input files===================
        file_list input_files = get_input_files(config);


    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Something went wrong!"<<std::endl;
        return 1;
    }

	return 0;
}

