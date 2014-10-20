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
#include <pni/io/nx/algorithms/create_field.hpp>
#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/tiff/tiff_reader.hpp>
namespace fs = boost::filesystem;

#include "../common/file_list_parser.hpp"
#include "../common/file_utils.hpp"
#include "utils.hpp"

#include "../common/image_utils.hpp"

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
    catch(cli_option_error &error)
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

//----------------------------------------------------------------------------
// Checks a field with an image 
//! 
//! \throws type_error if data types do not match
//! \throws shape_mismatch_error if shape or number of elements do not match
//!
void check_field(const h5::nxfield &detector_field,
                 const pni::io::image_info &info)
{
    //throw an exception if the data types do not match
    if(info.get_channel(0).type_id() != detector_field.type_id())
        throw type_error(EXCEPTION_RECORD,
                "Data types of field and image do not match!");

    if(detector_field.rank()!=3)
        throw shape_mismatch_error(EXCEPTION_RECORD,
                "The field must be of rank 3!");

    auto field_shape = detector_field.shape<shape_t>();
    if((field_shape[1]!=info.nx())||(field_shape[2]!=info.ny()))
        throw shape_mismatch_error(EXCEPTION_RECORD,
                "Frame shapes do not match!");
}

h5::nxfield create_field(const h5::nxgroup &detector_group,
                         const string &field_name,
                         const pni::io::image_info &info)
{
   return create_field(h5::nxobject(detector_group),
                       info.get_channel(0).type_id(),
                       field_name,
                       shape_t{0,info.nx(),info.ny()},
                       shape_t{1,info.nx(),info.ny()});
}

//----------------------------------------------------------------------------
h5::nxfield get_detector_field(const h5::nxgroup &detector_group,
                               const pni::io::image_info &info,
                               const configuration &config)
{
   string field_name = config.value<string>("data");

   if(!detector_group.has_child(field_name))
       //if the detector field does not exist we simply create it
       //this may throw all kinds of exceptions!
       return create_field(detector_group,field_name,info);
   else
   {
        //get the field - throws type_error if the child is not a field
        h5::nxfield detector_field = detector_group[field_name];

        //if the detector field has a finite size we will try to append the 
        //data
        if(detector_field.size())
        {
            check_field(detector_field,info);
            return detector_field;
        }
        //if the detector field exists but is empty - here we go the easy 
        //way - 
        else
        {
            detector_group.remove(field_name);
            return create_field(detector_group,field_name,info);
        }
   }
}

//----------------------------------------------------------------------------
void append_data(h5::nxfile &file, h5::nxfield &field,
                 const file_list &files)
{
    try
    {
        file_type type = get_file_type(files.front());
        //finally we need to process the data
        if(type==file_type::CBF)
            append_data(pni::io::cbf_reader(),file,field,files);
        else if(type == file_type::TIF )
            append_data(pni::io::tiff_reader(),file,field,files);
        
        //close the file 
        field.close();
        file.close();
    }
    catch(...)
    {
        std::cerr<<"Unkown error during appending data!"<<std::endl;
        std::exit(1);
    }
}

