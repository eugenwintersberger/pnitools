/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: 30.06.2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "det2nx.hpp"
#include "../common/config_utils.hpp"
#include "../common/file_list_parser.hpp"
#include "../common/file_utils.hpp"

static const string program_name = "det2nx";
static const string help_header = "det2nx takes the following command line options";

static const string_list cbf_exts = {".cbf",".CBF"};
static const string_list tif_exts = {".tif",".TIF",".tiff",".TIFF"};

int main(int argc,char **argv)
{
    //create configuration
    configuration config = create_configuration();

    if(argc<2)
    {
        std::cerr<<"det2nx called with to less arguments!"<<std::endl;
        std::cerr<<std::endl<<"Use det2nx -h for more information"<<std::endl;
        return 1;
    }
  
    //parse command line options and arguments
    if(parse_cli_opts(argc,argv,program_name,config)) return 1;

    //check if the user requested help 
    if(check_help_request(config,help_header)) return 1;

    bool verbose = config.value<bool>("verbose");

    //-------------------------generating the input file list------------------
    try
    {
        //------------------dealing with input data----------------------------
        //create the input file list - this will throw a file_error exception if
        //one of the input files does not exist
        auto infiles = file_list_parser::parse<file_list>(
                config.value<string_vector>("input-files"));
        if(verbose)
            std::cout<<"processing "<<infiles.size()<<" files ..."<<std::endl;

        //the first image in the stack determines the file type and all other
        //image paramters (like data type and shape)

        //at first we need to obtain the appropriate reader
        reader_ptr reader = get_reader(infiles,cbf_exts,tif_exts);

        //get thre reference image information object
        pni::io::image_info info = get_image_info(reader,infiles.begin()->path());

        //need to check all the input files
        check_input_files(infiles,reader,info);
       
        //--------------parse the nexus path to get target information----------
        nxpath nexus_path = path_from_string(config.value<string>("target"));
        
        //need to check the validity of the path
        if(nexus_path.filename().empty())
            throw file_error(EXCEPTION_RECORD,"No output file given!");

        if(!nexus_path.attribute().empty())
            throw file_error(EXCEPTION_RECORD,
                    "Nexus target must not be an attribute!");

        //------------------------opening the output file-----------------------
        //have to create the file name of the output file
        std::cout<<"create/open output target ..."<<std::endl;
        h5::nxfile output_file = open_output_file(nexus_path.filename(),
                                 config.value<bool>("overwrite"));
        nxobject_t root_group = h5::nxgroup(output_file["/"]);
        nxobject_t field = get_field(root_group,info,nexus_path,
                                      config.value<size_t>("deflate"));

        //------------------append the data------------------------------------
        //finally we need to process the data
        if(has_extension(*infiles.begin(),cbf_exts))
            append_data(pni::io::cbf_reader(),output_file,field,infiles);
        else if(has_extension(*infiles.begin(),tif_exts))
            append_data(pni::io::tiff_reader(),output_file,field,infiles);
        
        //close the file 
        close(field);
        output_file.close();

    }
    catch(file_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(cli_option_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(nxfield_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(nxfile_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::core::index_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(nxgroup_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(file_type_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }


	return 0;
}

