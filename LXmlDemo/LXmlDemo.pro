#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T21:56:00
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LXmlDemo
TEMPLATE = app


win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = release/LXmlDemo
        } else {
            target_path = build_/debug
            TARGET  = debug/LXmlDemo
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
            TARGET  = release/LXmlDemo
        } else {
            target_path = build_/debug
            TARGET  = debug/LXmlDemo
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
    parsedom.cpp

HEADERS  += widget.h \
    parsedom.h

FORMS    += widget.ui
