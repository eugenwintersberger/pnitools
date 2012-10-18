#include<QApplication>

#include "MainWidget.hpp"

int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    MainWidget mwidget;

    app.exec();
    return 0;
}
