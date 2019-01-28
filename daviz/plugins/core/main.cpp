#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QResource>
#include <QIcon>
#include <QDateTime>
#include <QFile>
#include <QPixmapCache>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(QLocale::system(), "RadarDisplay", ".", ":/translations");
    a.installTranslator(&translator);

    // 200MB
    QPixmapCache::setCacheLimit(200*1024);

    QResource::registerResource("icons.rcc");
    QIcon::setThemeName("oxygen");

    QFile file(":/styles/dark.css");
    file.open(QIODevice::ReadOnly);
    QString styleSheet(file.readAll());
    qApp->setStyleSheet(styleSheet);

    RadarDisplay::MainWindow w;
    w.showMaximized();
    
    return a.exec();
}
