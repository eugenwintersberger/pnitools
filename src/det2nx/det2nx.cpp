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
#include "../common/image_utils.hpp"
#include <pni/io/exceptions.hpp>
#include "../common/exceptions.hpp"



int main(int argc,char **argv)
{
    //get user configuration - if this fails the program is aborted
    configuration config = get_user_config(argc,argv);

    bool verbose = config.value<bool>("verbose");

    //------------------------------------------------------------------------
    //obtain input files - if this step fails abort the program

    if(verbose) std::cout<<"Obtain list of input files ...";

    file_list input_files = get_input_files(config);

    if(verbose) std::cout<<"success!"<<std::endl;

    //------------------------------------------------------------------------
    //obtain the basic image information - program is aborted if this fails
    if(verbose) std::cout<<"Read metadata of first frame ... ";

    image_info info;
    try
    {
        info = get_image_info(input_files.front());
    }
    catch(file_type_error &error)
    {
        std::cerr<<"Unsupported file format!"<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cerr<<"Unkown error while reading image information!"<<std::endl;
        return 1;
    }

    if(verbose) std::cout<<" success!"<<std::endl;

    //------------------------------------------------------------------------
    //optain the path to the detector group - if this fails abort program
    if(verbose) std::cout<<"Obtain detector path ... ";

    nxpath detector_path = get_detector_path(config);

    if(verbose) std::cout<<"success!"<<std::endl;

    //------------------------------------------------------------------------
    //obtain the target file - if this operation fails the program will 
    //abort
    if(verbose)
        std::cout<<"Open output file "<<detector_path.filename()<<" ... ";

    h5::nxfile detector_file = open_detector_file(detector_path);

    if(verbose) std::cout<<"success!"<<std::endl;

    //------------------------------------------------------------------------
    //open the detector group - if this operation fails the program will 
    //be aborted
    if(verbose) std::cout<<"Open detector group ... ";

    h5::nxgroup detector_group = get_detector_group(detector_file,
                                                    detector_path);

    if(verbose) std::cout<<"success!"<<std::endl;

    //-----------------------------------------------------------------------
    //append the data to the target
    if(verbose) std::cout<<"Open data field ... ";
    h5::nxfield detector_field = get_detector_field(detector_group,
                                                    info,
                                                    config);

    if(verbose) std::cout<<" success!"<<std::endl;

    //-------------------------------------------------------------------------
    //append data to the field
    append_data(detector_file,detector_field,input_files);

    //-------------------------generating the input file list------------------

	return 0;
}

