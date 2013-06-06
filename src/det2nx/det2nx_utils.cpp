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
 * Created on: Jun 5,2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "det2nx.hpp"
#include <pni/io/cbf_reader.hpp>
#include <pni/io/tiff_reader.hpp>
#include "../common/file_utils.hpp"


//------------------------------------------------------------------------
configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h",
                "show short help text",false));
    config.add_option(config_option<string>("target","t",
                "Nexus target where to store data",
                "output.nx:///:NXinstrument/:NXinstrument/:NXdetector/data"));
    config.add_option(config_option<bool>("append","a",
                "append data to existing field",true));
    config.add_argument(config_argument<string_vector>("input-files",-1,
                string_vector()));
    return config;
}

//-----------------------------------------------------------------------------
h5::nxfile open_output_file(const string &fname)
{
	fs::path output_file_path(fname);
	if((!fs::exists(output_file_path)))
		//if the file does not already exist we need to create it
        return h5::nxfile::create_file(fname);
    else
        //open an existing output file
        return h5::nxfile::open_file(fname);
}

//-----------------------------------------------------------------------------
reader_ptr get_reader(const file_list &flist,const string_list &cbf_exts,
                      const string_list &tiff_exts)
{
    if(flist.size())
    {
        if(has_extension(*flist.begin(),cbf_exts))
            return reader_ptr(new pni::io::cbf_reader());
        else if(has_extension(*flist.begin(),tiff_exts))
            return reader_ptr(new pni::io::tiff_reader());
        else
            throw file_type_error(EXCEPTION_RECORD,
                    "Unknown input file type!");
    }

    return reader_ptr(nullptr);
}

//-----------------------------------------------------------------------------
pni::io::image_info get_image_info(reader_ptr &reader,const string &path,
                                   size_t image_nr)
{
    if(!reader->filename().empty())
        reader->close(); //close the reader just in case that it is open
    reader->filename(path);
    reader->open();
    
    pni::io::image_info info = reader->info(image_nr);
    reader->close();
    return info;
}

//-----------------------------------------------------------------------------
void check_input_files(const file_list &flist,reader_ptr &reader,
                       const pni::io::image_info &ref_info,
                       size_t image_nr,size_t channel_nr)
{
    //close the reader in case that it is open
    if(!reader->filename().empty())
        reader->close();

    for(auto file:flist)
    {
        reader->filename(file.path());
        reader->open();
        pni::io::image_info info = reader->info(image_nr);
        //check shape
        if(!((ref_info.nx()==info.nx())&&
             (ref_info.ny()==info.ny())))
        {
            reader->close();
            throw shape_missmatch_error(EXCEPTION_RECORD,
                    "Image shapes do not match!");
        }

        //check data type
        if(ref_info.get_channel(channel_nr).type_id()!=
           info.get_channel(channel_nr).type_id())
        {
            reader->close();
            throw type_error(EXCEPTION_RECORD,
                    "Image data types do not match!");
        }

        reader->close();
    }

}
