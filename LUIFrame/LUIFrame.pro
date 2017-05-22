#-------------------------------------------------
#
# Project created by QtCreator 2017-05-20T11:16:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LDataTransTool
TEMPLATE = app

DEFINES +=DEBUG_OUT

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LDataTransTool_re
        } else {
            target_path = build_/debug
            TARGET  = LDataTransTool_de
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin

include ($$PWD/src/util/util.pri)
include ($$PWD/src/ui/ui.pri)

INCLUDEPATH +=$$PWD/src

SOURCES += \
    main.cpp

RESOURCES += \
    image.qrc
