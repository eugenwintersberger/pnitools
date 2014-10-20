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
    //get user configuration - abort program if this fails
    configuration config = create_default_configuration();
    if(!get_cli_config(argc,argv,config)) return 1;

    bool verbose = config.value<bool>("verbose");

    //------------------------------------------------------------------------
    //obtain input files - if this step fails abort the program

    try
    {
        //obtain the list of input files
        file_list input_files = get_input_files(config);

        //get info from the first image in the stack
        image_info info = get_image_info(input_files);
   
        //get the path to the detector
        nxpath detector_path = get_detector_path(config);
   
        //get the detector file
        h5::nxfile detector_file = open_detector_file(detector_path);
    
        h5::nxgroup detector_group = get_detector_group(detector_file,
                                                    detector_path);
        //-----------------------------------------------------------------------
        //append the data to the target
        h5::nxfield detector_field = get_detector_field(detector_group,
                                                        info,
                                                        config);

        //-------------------------------------------------------------------------
        //append data to the field
        append_data(detector_file,detector_field,input_files);
    }
    catch(program_error &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }

	return 0;
}

