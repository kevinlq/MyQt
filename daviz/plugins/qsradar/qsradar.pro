#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T22:58:16
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = QSRadar

include(../../davizplugin.pri)
include(../core/core.pri)

DEFINES += QSRADAR_LIBRARY
QT       += core gui network

SOURCES += \
    qsradarplugin.cpp \
    qsutil.cpp \
    qsradar.cpp

HEADERS  += \
    qsradarplugin.h \
    qsradar_global.h \
    qsutil.h \
    qsradar.h

INCLUDEPATH += $(QS_ROOT)/xxpoint \
    $(QS_ROOT)/xxtrack \
	$$PWD/../core

OTHER_FILES += \
    qsradar.pluginspec \
    QSRadar.json

TRANSLATIONS += \
    translations/QSRadar.zh_CN.ts

RESOURCES += \
    qsradar.qrc
