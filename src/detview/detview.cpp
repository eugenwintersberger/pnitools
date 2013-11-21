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
 * Created on: Nov 20, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <numeric>
#include <algorithm>
#include "detview.hpp"
#include "plot.hpp"
#include "../common/io_utils.hpp"
#include "../common/config_utils.hpp"


static const string program_name = "detview";


typedef image_type::value_type pixel_type;

int main(int argc,char **argv)
{
    configuration config = create_config();

    //---------------parse program configuration-------------------------------
    if(parse_cli_opts(argc,argv,program_name,config)) return 1;

    if(check_help_request(config,"Program usage")) return 1;

    try
    {
        //-------------------check if the user has passed an input file--------
        if(!config.has_option("input-file"))
        {
            std::cerr<<"No input file passed - see detview -h for "
                     <<"more information!"<<std::endl;
            return 1;
        }

        //------------------read input image-----------------------------------
        auto image = read_image<image_type>(config.value<string>("input-file"));        
        auto shape = image.shape<shape_t>();

        //-------------------show/output the image-----------------------------

        plstream stream(1,1,"qtwidget",nullptr);
        stream.init();
        stream.env(0,shape[0],0,shape[1],0,0);
        size_t nx = shape[0];
        size_t ny = shape[1];
        pixel_type min_value = *std::min_element(image.begin(),image.end());
        pixel_type max_value = *std::max_element(image.begin(),image.end());
        std::cout<<min_value<<" "<<max_value<<std::endl;
        stream.scmap1n(100);
        image_buffer buffer = image_buffer_from_array(image);
        stream.image(buffer.data(),nx,ny,0,nx,0,ny,min_value,max_value,0,nx,0,ny);
    }
    catch(file_error &error)
    {
        std::cout<<error<<std::endl;
        return 1;
    }
    catch(...)
    {
        std::cout<<"Something went wrong!"<<std::endl;
        return 1;
    }

    return 0;
}
