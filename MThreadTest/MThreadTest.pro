#-------------------------------------------------
#
# Project created by QtCreator 2017-05-15T08:29:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MThreadTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customthreadobject.cpp \
    appinittest.cpp

HEADERS  += mainwindow.h \
    customthreadobject.h \
    appinittest.h

FORMS    += mainwindow.ui
