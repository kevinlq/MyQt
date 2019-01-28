TARGET = PlotWatch

include(../../davizplugin.pri)
include(../../utils/utils.pri)
include(../core/core.pri)

TEMPLATE = lib
DEFINES += PLOTWATCH_LIBRARY
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    plotwatchplugin.cpp \
    recentplotwatchconfig.cpp \
    recentplotwatch.cpp \
    plotwatchmanager.cpp \
    plotwatchcontrol.cpp \
    plotlistview.cpp \
    plotlistmodel.cpp \
    iplotwatch.cpp

HEADERS += \
    plotwatchplugin.h \
    plotwatch_global.h \
    recentplotwatchconfig.h \
    recentplotwatch.h \
    plotwatchmanager.h \
    plotwatchcontrol.h \
    plotlistview.h \
    plotlistmodel.h \
    iplotwatch.h

FORMS += \
    recentplotwatchconfig.ui

OTHER_FILES += \
    plotwatch.pri \
    plotwatch.pluginspec \
    PlotWatch.json \
    icons/roll.png \
    icons/media-playback-start.png \
    icons/media-playback-pause.png \
    icons/list-add.png \
    icons/edit-clear.png \
    icons/configure.png \
    icons/dialog-warning.png


RESOURCES += \
    plotwatch.qrc

TRANSLATIONS += translations/PlotWatch.zh_CN.ts
