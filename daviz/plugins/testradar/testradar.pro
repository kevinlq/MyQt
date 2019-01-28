#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T22:58:16
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = TestRadar

include(../../davizplugin.pri)
include(../core/core.pri)

DEFINES += TESTRADAR_LIBRARY
QT       += core gui network

SOURCES += \
    testradarplugin.cpp \
    testradar.cpp

HEADERS  += \
    testradar_global.h \
    testradarplugin.h \
    testradar.h

OTHER_FILES += \
    testradar.pluginspec \
    TestRadar.json

RESOURCES += \
    testradar.qrc

TRANSLATIONS += \
    translations/TestRadar.zh_CN.ts
