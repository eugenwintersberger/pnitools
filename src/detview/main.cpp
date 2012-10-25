/*
 * main.cpp
 *
 *  Created on: Apr 20, 2011
 *      Author: Eugen Wintersberger
 */

#include<iostream>

#include<QtGui>

#include "MainWidget.hpp"


int main(int argc,char **argv){

	QApplication app(argc,argv);
	MainWidget mw;
    mw.show();
    mw.resize(1024,1024);

	return app.exec();
}
