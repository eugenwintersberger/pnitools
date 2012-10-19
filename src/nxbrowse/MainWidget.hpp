#ifndef __MAINWIDGET_HPP__
#define __MAINWIDGET_HPP__

#include<QTextEdit>
#include<QtGui>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QToolBar>

class MainWidget : public QMainWindow
{
    Q_OBJECT
    private:
        QTextEdit *editor;

        //some actions
        QAction *openAction;
        QAction *closeAction;
        QAction *exitAction;

        //tree-view and MDI widget
        QSplitter *splitter;
        QTreeView *treeview;
        QMdiArea *mdiarea;

        //menus and toolbar
        QMenu *fileMenu;
        QToolBar *toolbar;
        QStatusBar *statusbar;
    private slots:
        void open();
        void close();
        void quit();
    public:
        MainWidget();
};

#endif
