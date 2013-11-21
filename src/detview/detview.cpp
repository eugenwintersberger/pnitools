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

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include <mgl/mgl.h>
#include <mgl/mgl_qt.h>
#include "detview.hpp"
#include "../common/io_utils.hpp"
#include "../common/config_utils.hpp"


static const string program_name = "detview";


typedef image_type::value_type pixel_type;

class draw_image:public mglDraw
{
    private:
        mglData _data;
        mglData _cbar;
    public:
        template<typename ATYPE> draw_image(const ATYPE &a)
        {
            typedef typename ATYPE::value_type value_type;
            auto shape = a.template shape<shape_t>(); 
            _data = mglData(shape[0],shape[1]);
            _cbar = mglData(10);
            value_type min_value=0,max_value=0;
            //copy data to the mglData structure
            for(size_t i=0;i<shape[0];i++)
                for(size_t j=0;j<shape[1];j++)
                {
                    value_type value = a(i,j);
                    if(value<min_value) min_value = value;
                    else if(value>=max_value) max_value = value;

                    _data.Put(value,i,j);
                }

            std::cout<<min_value<<" "<<max_value<<std::endl;
            _cbar.Fill(min_value,max_value);
        }

        int Draw(mglGraph *d);
};

int draw_image::Draw(mglGraph *d)
{
    d->NewFrame();
    d->Box();
    d->SetRanges(0,_data.nx,0,_data.ny);
    d->CRange(_data);
    d->SetFunc("","","","lg(c+1)");
    d->SetTicks('c',0);
    d->Dens(_data);
    d->Colorbar();
    d->EndFrame();

    return d->GetNumFrame();
}

int main(int argc,char **argv)
{
    configuration config = create_config();
    QApplication app(argc,argv);

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

        //--------------setup the main application-----------------------------
        QMainWindow *main_window = new QMainWindow();
        main_window->resize(650,480);
        main_window->setWindowTitle(string("detview"+config.value<string>("input-file")).c_str());

        draw_image *draw = new draw_image(image);
        QMathGL *qmgl = new QMathGL();
        qmgl->autoResize =true;
        qmgl->setDraw(draw);
        qmgl->update();


        main_window->setCentralWidget(qmgl);
        main_window->show();
        app.exec();




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
