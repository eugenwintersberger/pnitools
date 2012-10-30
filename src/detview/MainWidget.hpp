#ifndef __MAINWIDGET_HPP__
#define __MAINWIDGET_HPP__

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QList>

#include<QVTKWidget.h>


#include "RenderingPipeline.hpp"
#include "IntensityRange.hpp"


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
        IntensityRange *irange; //!< intensity range for plotting

    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};
    

#endif
