#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T22:58:16
#
#-------------------------------------------------

TARGET = PPIView

include(../../davizplugin.pri)
include(../../utils/utils.pri)
include(../core/core.pri)

TEMPLATE = lib
DEFINES += PPIVIEW_LIBRARY
QT       += core gui network opengl 3d
CONFIG   += qt3d plugin
SOURCES += \
    ppiviewplugin.cpp \
    trackitem.cpp \
    ppiview.cpp \
    ppiglviewportitem.cpp \
    ppieffect.cpp \
    ppicontrol.cpp \
    coordsitem.cpp \
    trackpathitem.cpp

HEADERS  += \
    ppiviewplugin.h \
    ppiview_global.h \
    trackitem.h \
    ppiview.h \
    ppiglviewportitem.h \
    ppieffect.h \
    ppicontrol.h \
    coordsitem.h \
    trackpathitem.h

OTHER_FILES += \
    ppiview.pluginspec \
    shaders/ppieffect.frag \
    shaders/ppieffect.vert \
    PPIView.json

RESOURCES += \
    ppiview.qrc

TRANSLATIONS += \
    translations/PPIView.zh_CN.ts
