#include "mainwindow.h"
#include <QApplication>

#include "appinittest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppInitTest test;
    test.init();

    MainWindow w;
    w.show();

    return a.exec();
}
