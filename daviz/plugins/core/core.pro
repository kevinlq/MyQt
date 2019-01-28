#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T22:58:16
#
#-------------------------------------------------

TARGET = Core

include(../../davizplugin.pri)
include(rcc.pri)

TEMPLATE = lib
DEFINES += CORE_LIBRARY
QT       += core gui network opengl
CONFIG   += qt3d plugin
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 3d
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    mainwindow.cpp \
    coreplugin.cpp \
    icore.cpp \
    panelgroup.cpp \
    iview.cpp \
    panelwidget.cpp \
    viewgroup.cpp \
    radargroup.cpp \
    plugindialog.cpp \
    versiondialog.cpp \
    menumanager.cpp \
    iradar.cpp \
    paneltitlebar.cpp \
    viewcontrol.cpp

HEADERS  += \
    mainwindow.h \
    iradar.h \
    plotdata.h \
    targetdata.h \
    trackdata.h \
    coreplugin.h \
    core_global.h \
    icore.h \
    panelgroup.h \
    iview.h \
    panelwidget.h \
    viewgroup.h \
    radargroup.h \
    plugindialog.h \
    versiondialog.h \
    menumanager.h \
    coreconstant.h \
    paneltitlebar.h \
    viewcontrol.h

INCLUDEPATH += $(QS_ROOT)/xxpoint \
    $(QS_ROOT)/xxtrack

RESOURCES += \
    radardisplay.qrc \
    icons.qrc

#RCC_RESOURCES += \
#    icons.qrc

OTHER_FILES += \
#    icons.qrc \
    styles/dark.css \
    core.pluginspec \
    core.pri \
    Core.json \
    icons/draw-arrow-down.png \
    icons/draw-arrow-back.png \
    icons/zoom-original.png \
    icons/daviz.png

TRANSLATIONS += translations/Core.zh_CN.ts
