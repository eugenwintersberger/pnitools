#pragma once
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


#include<pni/core/types.hpp>
#include<pni/core/arrays.hpp>
#include<pni/core/rbuffer.hpp>
#include<pni/io/image_info.hpp>
#include<pni/io/cbf_reader.hpp>
#include<pni/io/tiff_reader.hpp>

#include<algorithm>

using namespace pni::core;
using namespace pni::io;

typedef darray<float64> array_t;
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
        void rangeChanged(float64 min,float64 max);
    public:
        //----------------------------------------------------------------------
        RenderingPipeline(QVTKWidget *w);

        //----------------------------------------------------------------------
        ~RenderingPipeline();
        //----------------------------------------------------------------------
        //! return maximum of image data
        double getMax() const;

        //----------------------------------------------------------------------
        //! return minimum of image data
        double getMin() const;

        //----------------------------------------------------------------------
        /*!
        \brief reset lookup table

        Reset the lookup table to the original data range of the image.
        */
        void resetLookupTable();

        //----------------------------------------------------------------------
        void update();

        //----------------------------------------------------------------------
        void loadData(const string &path);
};
