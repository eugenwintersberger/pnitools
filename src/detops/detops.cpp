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

#include "../common/config_utils.hpp"
#include "../common/file.hpp"
#include "../common/file_list_parser.hpp"
#include <pni/io/parsers/slice_parser.hpp>


//list of file names
typedef std::vector<string> file_name_list;
//list of file objects
typedef std::vector<file> file_list;

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
    
    //read the background file if requested     
    array_t background_data;
    if(config.has_option("background")) { }

    //read the mask file if requested - before we check input files (see above)
    if(config.has_option("mask")) { }

    //setup rois (if there are any)
   
    //=================now we read the fetch the input files===================

    //next we have to get the input files
    auto input_files = file_list_parser::parse<file_list>(
                        config.value<file_name_list>("input-files"));


    try
    {
        //now we have to iterate over all input files
        for(auto infile: input_files)
        {
            //read the input file
            array_t data = read_image(infile);

            //process the data


        }
    }
    catch(...)
    {
        std::cerr<<"Something went wrong!"<<std::endl;
    }

	return 0;

}

