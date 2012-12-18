#include "MainWidget.hpp"

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

    //create the main widget layoutq
    splitter = new QSplitter();
    treeview = new QTreeView(splitter);
    mdiarea = new QMdiArea(splitter);


    //fill the vertical layout
    toolbar = new QToolBar();
    addToolBar(toolbar);

    statusbar = new QStatusBar();
    setStatusBar(statusbar);

    setCentralWidget(splitter);

    setWindowTitle("Nexus file browser");
}

void MainWidget::open()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("open file"),
            tr("HDF5 files (*.h5)"));

    if(filename != "")
    {
        try
        {
            file_list.append(NXFile(NXFile::open_file(filename.toStdString(),true)));
        }
        catch(pni::nx::NXFileError &error)
        {
            std::cerr<<"Error opening file"<<std::endl;
        }

        //we have to add the newly opened file to the Model list.
        NexusFileModel *model = new NexusFileModel(f);
        treeview->setModel(model);
    }
}

void MainWidget::close()
{
    //get the selected file in the model view and close the file
    
}

void MainWidget::quit()
{
    qApp->quit();
}
