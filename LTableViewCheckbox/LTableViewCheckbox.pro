#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T20:03:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LTableViewCheckbox
TEMPLATE = app


win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = LTableViewCheckbox_re
        } else {
            target_path = build_/debug
            TARGET  = LTableViewCheckbox_de
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin

SOURCES += main.cpp\
        widget.cpp \
    tablemodel.cpp \
    checkboxdelegate.cpp

HEADERS  += widget.h \
    tablemodel.h \
    checkboxdelegate.h \
    gdatadef.h

FORMS    += widget.ui
