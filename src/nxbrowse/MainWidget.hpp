#ifndef __MAINWIDGET_HPP__
#define __MAINWIDGET_HPP__

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>

class MainWidget : public QMainWindow
{
    Q_OBJECT
    private:
        QTextEdit *editor;
        QVBoxLayout layout;

        //some actions
        QAction *openAction;
        QAction *closeAction;
        QAction *exitAction;

        QMenu *fileMenu;
        //menu
    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};

#endif
