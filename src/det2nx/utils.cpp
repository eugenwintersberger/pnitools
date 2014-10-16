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
// Created on: Oct 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/filesystem.hpp> 
namespace fs = boost::filesystem;

#include "../common/file_list_parser.hpp"
#include "utils.hpp"

//----------------------------------------------------------------------------
file_list get_input_files(const configuration &config)
{
    file_list input_files;

    try
    {
        auto file_names = config.value<string_vector>("input-files");
        input_files = file_list_parser::parse<file_list>(file_names);
        if(config.value<bool>("verbose"))
            std::cout<<"processing "<<input_files.size()<<" files ..."<<std::endl;
    }
    catch(parser_error &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Unknown error while parsing input file list!"<<std::endl;
        std::exit(1);
    }

    return input_files;

}

//----------------------------------------------------------------------------
nxpath get_detector_path(const configuration &config)
{
    nxpath detector_path;

    //we first parse the group option - this provides the path to the 
    //detector group in the file
    try
    {
        detector_path = nxpath::from_string(config.value<string>("group"));
    }
    catch(parser_error &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Unkown error while parsing detector group  path!";
        std::cerr<<std::endl;
        std::exit(1);
    }
   
    //if the group path does not include the filename we check 
    //the 'file' option
    if(detector_path.filename().empty() && config.has_option("file"))
        detector_path.filename(config.value<string>("file"));
    else
    {
        std::cerr<<"The target path does not contain a filename!"<<std::endl;
        std::exit(1);
    }
    
    //finally we have to check if the group path does not refer to an 
    //attribute
    if(!detector_path.attribute().empty())
    {
        std::cerr<<"The target must be a field - an attribute was given!";
        std::cerr<<std::endl;
        std::exit(1);
    }

    return detector_path;
}

//-----------------------------------------------------------------------------
h5::nxfile open_detector_file(const nxpath &detector_path)
{
	fs::path output_file_path(detector_path.filename());
	if((!fs::exists(output_file_path)))
    {
        std::cerr<<"File does not exist!"<<std::endl;
        std::exit(1);
    }
    else
        //open an existing output file
        return h5::nxfile::open_file(detector_path.filename(),false);
}

//----------------------------------------------------------------------------
h5::nxgroup get_detector_group(const h5::nxfile &detector_file,
                               const nxpath &detector_path)
{
    try
    {
        return get_object(detector_file.root(),
                          detector_path);
    }
    catch(key_error &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    catch(...)
    {
        std::cerr<<"Unkown error while opening the detector group!";
        std::cerr<<std::endl;
        std::exit(1);
    }
}
