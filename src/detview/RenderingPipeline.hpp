#ifndef __RENDERINGPIPELINE_HPP__
#define __RENDERINGPIPELINE_HPP__

#include <vtkSmartPointer.h>
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageViewer2.h>
#include <vtkLookupTable.h>
#include <vtkImageLogarithmicScale.h>


#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>

#include<algorithm>

using namespace pni::utils;

typedef DArray<Float64> array_t;
typedef array_t::storage_type buffer_t;


class RenderingPipeline:public QObject
{
    Q_OBJECT
    private:
        vtkSmartPointer<vtkDoubleArray> image_array;
        vtkSmartPointer<vtkImageViewer2> image_viewer;
        vtkSmartPointer<vtkImageData> image_data;
        vtkSmartPointer<vtkLookupTable> lookup_table;
        QVTKWidget *widget;
    public slots:
        void setLogScale();
        void setLinScale();
        void rotateRight();
        void rotateLeft();
    public:
        RenderingPipeline(QVTKWidget *w,const array_t &a);

        ~RenderingPipeline();


        void setData(const array_t &a);
};

#endif
