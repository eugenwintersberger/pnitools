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
#include "../common/nexus_utils.hpp"


//------------------------------------------------------------------------
configuration create_configuration()
{
    configuration config;
    config.add_option(config_option<bool>("help","h",
                "show short help text",false));
    config.add_option(config_option<string>("target","t",
                "Nexus target where to store data",
                "output.nx:///:NXinstrument/:NXinstrument/:NXdetector/data"));
    config.add_option(config_option<bool>("verbose","v",
                "print verbose output",false));
//    config.add_option(config_option<bool>("append","a",
 //               "append data to existing field",true));
    config.add_argument(config_argument<string_vector>("input-files",-1,
                string_vector()));
    config.add_option(config_option<bool>("overwrite","",
                "overwrite existing data file",false));
    config.add_option(config_option<size_t>("deflate","d",
                "set deflate level",size_t(0)));

    return config;
}

//-----------------------------------------------------------------------------
h5::nxfile open_output_file(const string &fname,bool overwrite)
{
	fs::path output_file_path(fname);
	if((!fs::exists(output_file_path))||overwrite)
		//if the file does not already exist we need to create it
        return h5::nxfile::create_file(fname,overwrite);
    else
        //open an existing output file
        return h5::nxfile::open_file(fname,false);
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

//-----------------------------------------------------------------------------
h5::nxfield get_field(const h5::nxfile &ofile,const pni::io::image_info &info,
                      const nxpath &path,size_t deflate) 
{
    h5::nxgroup group = ofile["/"];
    h5::nxfield field;
    h5::nxdeflate_filter filter(deflate,true);

    auto iter = path.begin();
    auto fiter = path.begin();
    advance(fiter,path.size()-1);

    while(iter!=path.end())
    {
        if(iter==fiter)
        {
            //we have reached the last element - need to check for a field
            std::cout<<"look for field "<<iter->first<<std::endl;
            if(group.exists(iter->first))
            {
                std::cout<<"opening field "<<iter->first<<std::endl;
                field = group[iter->first]; //append data if field exists
            }
            else
            {
                std::cout<<"creating field "<<iter->first<<std::endl;
                //create the field and start from scratch
                if(deflate)
                    create_field(group,iter->first,info.get_channel(0).type_id(),
                                 shape_t{0,info.nx(),info.ny()},field,filter);
                else
                    create_field(group,iter->first,info.get_channel(0).type_id(),
                                 shape_t{0,info.nx(),info.ny()},field);
            }
        }
        else
            get_group(group,iter->first,iter->second,group);

        //increment iterator
        ++iter;
    }

    return field;
}
