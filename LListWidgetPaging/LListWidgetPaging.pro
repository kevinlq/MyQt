#-------------------------------------------------
#
# Project created by QtCreator 2017-11-21T22:22:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LListWidgetPaging
TEMPLATE = app

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = release/LListWidgetPaging
        } else {
            target_path = build_/debug
            TARGET  = debug/LListWidgetPaging
        }
        DESTDIR = $$PWD/Bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += $$PWD/Bin

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
