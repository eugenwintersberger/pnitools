//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: 30.06.2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//#include "det2nx.hpp"
#include "config.hpp"
#include "utils.hpp"
#include "../common/file_list_parser.hpp"
#include "../common/file_utils.hpp"
#include <pni/io/exceptions.hpp>



int main(int argc,char **argv)
{
    //get user configuration - if this fails the program is aborted
    configuration config = get_user_config(argc,argv);

    //------------------------------------------------------------------------
    //obtain input files - if this step fails abort the program

    if(config.value<bool>("verbose")) 
        std::cout<<"Obtain list of input files ...";

    file_list input_files = get_input_files(config);

    if(config.value<bool>("verbose")) std::cout<<"success!"<<std::endl;

    //------------------------------------------------------------------------
    //optain the path to the detector group - if this fails abort program
    nxpath detector_path = get_detector_path(config);

    //------------------------------------------------------------------------
    //obtain the target file - if this operation fails the program will 
    //abort
    if(config.value<bool>("verbose"))
        std::cout<<"Open output file "<<detector_path.filename()<<" ... ";

    h5::nxfile detector_file = open_detector_file(detector_path);

    if(config.value<bool>("verbose")) std::cout<<"success!"<<std::endl;

    //------------------------------------------------------------------------
    //open the detector group - if this operation fails the program will 
    //be aborted
    if(config.value<bool>("verbose")) std::cout<<"Open detector group ... ";

    h5::nxgroup detector_group = get_detector_group(detector_file,
                                                    detector_path);

    if(config.value<bool>("verbose")) std::cout<<"success!"<<std::endl;

    //append the data to the target
                                                    

    //-------------------------generating the input file list------------------
    try
    {
        //------------------------opening the output file-----------------------
        //have to create the file name of the output file
        /*
        h5::nxobject field = get_field(root_group,info,nexus_path,
                                       config.value<size_t>("deflate"));

        //------------------append the data------------------------------------
        //finally we need to process the data
        if(has_extension(*infiles.begin(),cbf_exts))
            append_data(pni::io::cbf_reader(),output_file,field,infiles);
        else if(has_extension(*infiles.begin(),tif_exts))
            append_data(pni::io::tiff_reader(),output_file,field,infiles);
        
        //close the file 
        close(field);
        */
        detector_file.close();

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
    catch(pni::io::io_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::core::index_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(pni::io::object_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(type_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }


	return 0;
}

