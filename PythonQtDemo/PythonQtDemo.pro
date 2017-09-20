#-------------------------------------------------
#
# Project created by QtCreator 2017-09-20T19:40:30
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PythonQtDemo
TEMPLATE = app

CONFIG  += console
CONFIG  -=app_bundle

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = /release/PythonQtDemo
        } else {
            target_path = build_/debug
            TARGET  = /debug/PythonQtDemo
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin


INCLUDEPATH += $$PWD/include

LIBS    += -L$$PWD/libs/ -lpython27

SOURCES += main.cpp
