#ifndef __MAINWIDGET_HPP__
#define __MAINWIDGET_HPP__

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>
#include<QList>

#include "DetectorPlotWidget.hpp"


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
        
        DetectorPlotWidget *plot_widget;
        

    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};

#endif
