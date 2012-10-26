
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


    //fill the vertical layout
    toolbar = new QToolBar();
    addToolBar(toolbar);

    statusbar = new QStatusBar();
    setStatusBar(statusbar);

    //create the vtk widget
    vtkwidget = new QVTKWidget();

    //create the rendering pipeline - during program startup no image is loaded
    //and we just set the pointer to nullptr
    pipeline = nullptr; 
    
    setCentralWidget(vtkwidget);

    setWindowTitle("Detector viewer");
}

//-----------------------------------------------------------------------------
void MainWidget::open()
{

    QFileInfo fileinfo(QFileDialog::getOpenFileName(this,tr("open file"),"",
            tr("CBF files (*.cbf);;TIFF files (*.tif *.tiff)")));

    ImageInfo info;
    buffer_t buffer;
    //choose the proper reader
    if(fileinfo.suffix()==QString("cbf"))
    {
        //open the file
        CBFReader reader(fileinfo.absoluteFilePath().toStdString());
        info=reader.info(0); //get file information
        buffer = reader.image<buffer_t>(0); 
    }
    else if(fileinfo.suffix() == QString("tif"))
    {
        TIFFReader reader(fileinfo.absoluteFilePath().toStdString());
        info = reader.info(0);
        buffer = reader.image<buffer_t>(0);
    }
    
    shape_t shape{info.nx(),info.ny()};

    //set the new array data
    detector_data = array_t(shape,std::move(buffer));
    if(pipeline)
        pipeline->setData(detector_data);
    else
    {
        pipeline = new RenderingPipeline(vtkwidget,detector_data);
        connect(logscaleAction,SIGNAL(triggered()),pipeline,SLOT(setLogScale()));
        connect(linscaleAction,SIGNAL(triggered()),pipeline,SLOT(setLinScale()));
    }

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
