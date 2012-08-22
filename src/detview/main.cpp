/*
 * main.cpp
 *
 *  Created on: Apr 20, 2011
 *      Author: Eugen Wintersberger
 */

#include<iostream>

#include<Qt/QtGui>
#include<QVTKWidget.h>
#include<vtkImageViewer2.h>
#include<vtkRenderWindow.h>
#include<vtkJPEGReader.h>


class MainWindow:public QMainWindow{
protected:
	QAction *_close_action;
	QAction *_toggle_lin_log;
	QAction *_set_colormap;
	QVTKWidget *_vtk_widget;
	QWidget *_central_widget;
	vtkImageViewer2 *_image_viewer;
	vtkJPEGReader *_reader;
public:
	MainWindow();
	virtual ~MainWindow();

	virtual void createMenu();
	virtual void createToolBar();
	virtual void createStatusBar();
	virtual void createCenterWidget();
};

MainWindow::MainWindow():QMainWindow(){
	//need to construct the basic actions
	_close_action   = new QAction(this);
	_close_action->setText("Close ...");
	connect(_close_action,SIGNAL(triggered()),this,SLOT(close()));
	_toggle_lin_log = new QAction(this);
	_set_colormap   = new QAction(this);

	createMenu();
	createToolBar();
	createStatusBar();
}

MainWindow::~MainWindow(){
	if( _close_action != NULL ) delete _close_action;
	if( _toggle_lin_log != NULL ) delete _toggle_lin_log;
	if( _set_colormap != NULL ) delete _set_colormap;
}

void MainWindow::createCenterWidget(){
	_image_viewer = vtkImageViewer2::New();
	_central_widget = new QWidget(this);
	_vtk_widget = new QVTKWidget(_central_widget);

	setCentralWidget(_central_widget);

	_reader->SetFileName("/home/eugen/Desktop/DSCF0031.JPG");
	_reader->Update();

	_image_viewer->SetInput(_reader->GetOutput());
	vtkRenderWindow *rw = _vtk_widget->GetRenderWindow();
	rw->AddRenderer(_image_viewer->GetRenderer());
	_image_viewer->GetRenderer()->ResetCamera();
}

void MainWindow::createToolBar(){
	QToolBar *tb = new QToolBar("testtoolbar",this);

	addToolBar(Qt::TopToolBarArea,tb);
}

void MainWindow::createStatusBar(){
	QStatusBar *sb = new QStatusBar(this);

	setStatusBar(sb);
}

void MainWindow::createMenu(){
	QMenuBar *mbar = menuBar();

	QMenu *m;
	//set up the file menu
	m = mbar->addMenu("File");
	m->addAction("Open ...");
	m->addSeparator();
	m->addAction(_close_action);

}

int main(int argc,char **argv){

	QApplication app(argc,argv);
	MainWindow mw;

	mw.resize(100,100);
	mw.show();


	return app.exec();
}
