#include<QApplication>

#include "MainWidget.hpp"

int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    MainWidget mwidget;
    mwidget.show();

    app.exec();
    return 0;
}
