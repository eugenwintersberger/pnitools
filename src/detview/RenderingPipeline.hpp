#ifndef __RENDERINGPIPELINE_HPP__
#define __RENDERINGPIPELINE_HPP__

#include <vtkSmartPointer.h>
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageViewer2.h>
#include <vtkTIFFReader.h>
#include <vtkLookupTable.h>
#include <vtkImageLogarithmicScale.h>
#include <vtkScalarBarActor.h>
#include <vtkImageChangeInformation.h>


#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>
#include<pni/utils/RBuffer.hpp>
#include<pni/utils/io/ImageInfo.hpp>
#include<pni/utils/io/CBFReader.hpp>
#include<pni/utils/io/TIFFReader.hpp>

#include<algorithm>

using namespace pni::utils;
using namespace pni::io;

typedef DArray<Float64> array_t;
typedef array_t::storage_type buffer_t;


class RenderingPipeline:public QObject
{
    Q_OBJECT
    private:
        vtkSmartPointer<vtkTIFFReader> tiff_reader;
        vtkSmartPointer<vtkImageViewer2> image_viewer;
        vtkSmartPointer<vtkLookupTable> lookup_table;
        vtkSmartPointer<vtkScalarBarActor> color_bar;
        vtkSmartPointer<vtkImageChangeInformation> image_info;
        QVTKWidget *widget;
    public slots:
        void setLogScale();
        void setLinScale();
        void rotateRight();
        void rotateLeft();
        void rangeChanged(Float64 min,Float64 max);
    public:
        RenderingPipeline(QVTKWidget *w);



        //---------------------------------------------------------------------
        void loadData(const String &path)
        {
            tiff_reader->SetFileName(path.c_str());
            tiff_reader->Update();

            image_info->Update();
            image_viewer->Render();
            

        }


        ~RenderingPipeline();
};

#endif
