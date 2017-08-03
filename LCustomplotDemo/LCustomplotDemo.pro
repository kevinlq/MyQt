#-------------------------------------------------
#
# Project created by QtCreator 2017-07-29T22:35:38
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LCustomplotDemo
TEMPLATE = app

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LCustomplotDemo
        } else {
            target_path = build_/debug
            TARGET  = LCustomplotDemo
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}


DEPENDPATH += bin

include ($$PWD/qcustomplot/qcustomplot.pri)
INCLUDEPATH +=$$PWD/qcustomplot

SOURCES += main.cpp\
        frmmain.cpp

HEADERS  += frmmain.h

FORMS    += frmmain.ui
