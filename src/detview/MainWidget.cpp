
#include<QFileInfo>
#include "MainWidget.hpp"



//-----------------------------------------------------------------------------
MainWidget::MainWidget()
{
    openAction = new QAction(tr("&open"),this);
    closeAction = new QAction(tr("&close"),this);
    exitAction = new QAction(tr("&exit"),this);
    logscaleAction = new QAction(tr("&log10 view"),this);
    linscaleAction = new QAction(tr("l&inear view"),this);
    rotateLeft = new QAction(tr("rotate &left"),this);
    rotateRight = new QAction(tr("rotate &right"),this);
    
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(exitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    //add the file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);

    //add the view menu
    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(logscaleAction);
    viewMenu->addAction(linscaleAction);
    viewMenu->addAction(rotateLeft);
    viewMenu->addAction(rotateRight);


    //fill the vertical layout
    toolbar = new QToolBar();
    addToolBar(toolbar);

    statusbar = new QStatusBar();
    setStatusBar(statusbar);

    //create the vtk widget
    vtkwidget = new QVTKWidget();
    setCentralWidget(vtkwidget);


    //create the rendering pipeline - during program startup no image is loaded
    //and we just set the pointer to nullptr
    pipeline = new RenderingPipeline(vtkwidget);
    connect(logscaleAction,SIGNAL(triggered()),pipeline,SLOT(setLogScale()));
    connect(linscaleAction,SIGNAL(triggered()),pipeline,SLOT(setLinScale()));
    connect(rotateLeft,SIGNAL(triggered()),pipeline,SLOT(rotateLeft()));
    connect(rotateRight,SIGNAL(triggered()),pipeline,SLOT(rotateRight()));

    vtkwidget->show();

    setWindowTitle("Detector viewer");
}

//-----------------------------------------------------------------------------
void MainWidget::open()
{

    QFileInfo fileinfo(QFileDialog::getOpenFileName(this,tr("open file"),"",
            tr("CBF files (*.cbf);;TIFF files (*.tif *.tiff)")));


    pipeline->loadData(fileinfo.absoluteFilePath().toStdString());
}

//-----------------------------------------------------------------------------
void MainWidget::close()
{
    //get the selected file in the model view and close the file
    
}

//-----------------------------------------------------------------------------
void MainWidget::quit()
{
    qApp->quit();
}
