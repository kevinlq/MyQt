#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T22:58:16
#
#-------------------------------------------------

TARGET = EView

include(../../davizplugin.pri)
include(../../utils/utils.pri)
include(../core/core.pri)

TEMPLATE = lib
DEFINES += EVIEW_LIBRARY
#QT       += core gui network opengl 3d
QT       += core gui network opengl
CONFIG   += qt3d plugin
SOURCES += \
    eviewplugin.cpp \
    eview.cpp \
    eviewportitem.cpp \
    sweepeffect.cpp \
    coordsitem.cpp \
    rangefiltereffect.cpp \
    trackpathitem.cpp \
    trackitem.cpp \
    econtrol.cpp \

HEADERS  += \
    eview_global.h \
    eviewplugin.h \
    eview.h \
    eviewportitem.h \
    sweepeffect.h \
    coordsitem.h \
    rangefiltereffect.h \
    trackpathitem.h \
    trackitem.h \
    econtrol.h

OTHER_FILES += \
    eview.pluginspec \
    shaders/rangefilter.vert \
    shaders/rangefilter.frag \
    shaders/sweepeffect.frag \
    shaders/sweepeffect.vert \
    EView.json

RESOURCES += \
    eview.qrc

TRANSLATIONS += \
    translations/EView.zh_CN.ts
