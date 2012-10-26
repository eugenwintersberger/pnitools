#ifndef __MAINWIDGET_HPP__
#define __MAINWIDGET_HPP__

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QList>

#include<QVTKWidget.h>

#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>
#include<pni/utils/io/CBFReader.hpp>
#include<pni/utils/io/TIFFReader.hpp>

#include "RenderingPipeline.hpp"


using namespace pni::utils;
using namespace pni::io;


typedef DArray<Float64> array_t;
typedef array_t::storage_type buffer_t;



class MainWidget : public QMainWindow
{
    Q_OBJECT
    private:
        //some actions
        QAction *openAction;  //!< open file action
        QAction *closeAction; //!< close file action
        QAction *exitAction;  //!< exit program action
        QAction *logscaleAction; //!< change to logarithmic scale
        QAction *linscaleAction; //!< change to linear scale
        QAction *rotateLeft;
        QAction *rotateRight;

        //menus and toolbar
        QMenu *fileMenu;      //!< file menu
        QMenu *viewMenu;      //!< view options menu
        QToolBar *toolbar;    //!< toolbar widget
        QStatusBar *statusbar; //!< statusbar

        QVTKWidget *vtkwidget;  //!< the VTK rendering widget
        RenderingPipeline *pipeline; //!< the VTK rendering pipeline

        /*! 
        \brief the global data array
        
        This array holds the data of the actually loaded image frame. 
        All detector data is actually converted to Float64.
        */
        array_t detector_data;
    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};

#endif
