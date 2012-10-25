#ifndef __MAINWIDGET_HPP__
#define __MAINWIDGET_HPP__

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QList>

#include<QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageViewer2.h>


#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>
#include<pni/utils/io/CBFReader.hpp>
#include<pni/utils/io/TIFFReader.hpp>


using namespace pni::utils;
using namespace pni::io;


typedef DArray<Float64> array_t;
typedef array_t::storage_type buffer_t;

class RenderingPipeline
{
    private:
        vtkDoubleArray *array;
        vtkImageViewer2 *viewer;
        vtkImageData *idata;
        QVTKWidget *widget;
    public:
        RenderingPipeline(QVTKWidget *w):
            array(vtkDoubleArray::New()),
            viewer(vtkImageViewer2::New()),
            idata(vtkImageData::New()),
            widget(w)
        {
            idata->GetPointData()->SetScalars(array);

            idata->SetScalarType(VTK_DOUBLE);
            idata->SetSpacing(1.0,1.0,1.0);
            idata->SetOrigin(0,0,0);

            viewer->SetInput(idata);
            viewer->SetZSlice(0);

            widget->GetRenderWindow()->AddRenderer(viewer->GetRenderer());
        }

        void setData(const array_t &a)
        {
            array->SetArray(const_cast<Float64*>(a.storage().ptr()),
                         a.size(),1);
            auto s = a.shape<shape_t>(); 
            idata->SetDimensions(s[1],s[0],1);

        }



};


class MainWidget : public QMainWindow
{
    Q_OBJECT
    private:
        //some actions
        QAction *openAction;
        QAction *closeAction;
        QAction *exitAction;

        //menus and toolbar
        QMenu *fileMenu;
        QToolBar *toolbar;
        QStatusBar *statusbar;

        QVTKWidget *vtkwidget;
        RenderingPipeline *pipeline;

        //! the global data array
        array_t detector_data;

        
        

    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};

#endif
