#include "mainwindow.h"
#include "filedata.h"
#include "resfitter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setAcceptDrops(true);
    w.show();

    return a.exec();
}
