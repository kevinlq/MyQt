#-------------------------------------------------
#
# Project created by QtCreator 2017-06-13T20:42:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LSerialPortThread
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LSerialPortThread_re
        } else {
            target_path = build_/debug
            TARGET  = LSerialPortThread_de
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}
unix{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LSerialPortThread_re
        } else {
            target_path = build_/debug
            TARGET  = LSerialPortThread_de
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin

include ($$PWD/3rdparty/3rdparty.pri)

INCLUDEPATH +=$$PWD/3rdparty/serialport

SOURCES += main.cpp\
        widget.cpp \
    serialportobj.cpp

HEADERS  += widget.h \
    serialportobj.h

FORMS    += widget.ui

message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the LSerialPortThread will create in folder: $$target_path)
