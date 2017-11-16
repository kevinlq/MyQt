#-------------------------------------------------
#
# Project created by QtCreator 2017-11-16T20:44:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMThreadOP
TEMPLATE = app


include ($$PWD/common.pri)

SOURCES += main.cpp\
        widget.cpp \
    messagequeue.cpp \
    workdaatathread.cpp

HEADERS  += widget.h \
    messagequeue.h \
    workdaatathread.h

FORMS    += widget.ui
