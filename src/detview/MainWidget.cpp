
#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>
#include<pni/utils/io/CBFReader.hpp>
#include<pni/utils/io/TIFFReader.hpp>

#include<QFileInfo>
#include "MainWidget.hpp"


using namespace pni::utils;
using namespace pni::io;

MainWidget::MainWidget()
{
    openAction = new QAction(tr("&open"),this);
    closeAction = new QAction(tr("&close"),this);
    exitAction = new QAction(tr("&exit"),this);
    
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(exitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);


    //fill the vertical layout
    toolbar = new QToolBar();
    addToolBar(toolbar);

    statusbar = new QStatusBar();
    setStatusBar(statusbar);

    //create the plot widget
    plot_widget = new DetectorPlotWidget();

    setCentralWidget(plot_widget);

    setWindowTitle("Nexus file browser");
}

void MainWidget::open()
{
    typedef DArray<Float64> array_t;
    typedef array_t::storage_type buffer_t;

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
    array_t data(shape,std::move(buffer));

    plot_widget->setData(std::move(data));
}

void MainWidget::close()
{
    //get the selected file in the model view and close the file
    
}

void MainWidget::quit()
{
    qApp->quit();
}
