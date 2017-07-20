#-------------------------------------------------
#
# Project created by QtCreator 2017-07-20T15:13:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LPieChartDemo
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x


DEPENDPATH += bin

SOURCES += main.cpp\
        widget.cpp \
    lpiechart.cpp \
    lpiechart2.cpp

HEADERS  += widget.h \
    lpiechart.h \
    lpiechart2.h

FORMS    += widget.ui
