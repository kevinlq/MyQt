#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T19:30:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LQSystemPathOP
TEMPLATE = app

DEFINES +=DEBUG_OUT

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = release/LQSystemPathOP
        } else {
            target_path = build_/debug
            TARGET  = debug/LQSystemPathOP
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
