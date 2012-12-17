#pragma once

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QList>

#include<QVTKWidget.h>


#include "RenderingPipeline.hpp"


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
        QAction *rotateLeft;     //!< rotate image to the left
        QAction *rotateRight;    //!< rotate image to the right

        //menus and toolbar
        QMenu *fileMenu;      //!< file menu
        QMenu *viewMenu;      //!< view options menu
        QToolBar *toolbar;    //!< toolbar widget
        QStatusBar *statusbar; //!< statusbar

        QVTKWidget *vtkwidget;  //!< the VTK rendering widget
        RenderingPipeline *pipeline; //!< the VTK rendering pipeline

    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};
