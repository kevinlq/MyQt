#-------------------------------------------------
#
# Project created by QtCreator 2017-07-14T22:48:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LSerialTool
TEMPLATE = app

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LSerialTool_re
        } else {
            target_path = build_/debug
            TARGET  = LSerialTool_de
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
            TARGET  = LSerialTool_re
        } else {
            target_path = build_/debug
            TARGET  = LSerialTool_de
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin

include($$PWD/Src/3rdparty/3rdparty.pri)
include($$PWD/Src/ui/ui.pri)
include($$PWD/Src/bean/bean.pri)

INCLUDEPATH +=$$PWD/Src/3rdparty/serialport
INCLUDEPATH +=$$PWD/Src/ui
INCLUDEPATH +=$$PWD/Src/bean

SOURCES += main.cpp


message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the LSerialTool will create in folder: $$target_path)
