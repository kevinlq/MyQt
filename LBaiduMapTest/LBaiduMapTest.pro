#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T11:16:41
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LBaiduMapTest
TEMPLATE = app

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LBaiduMapTest_re
        } else {
            target_path = build_/debug
            TARGET  = LBaiduMapTest_de
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
