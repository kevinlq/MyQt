TARGET = TrackListView

include(../../davizplugin.pri)
include(../../utils/utils.pri)
include(../core/core.pri)

TEMPLATE = lib
DEFINES += TRACKLISTVIEW_LIBRARY
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    tracklistviewplugin.cpp \
    tracklistview.cpp \
    tracklistmodel.cpp

HEADERS += \
    tracklistview_global.h \
    tracklistviewplugin.h \
    tracklistmodel.h \
    tracklistview.h

OTHER_FILES += \
    tracklistview.pri \
    tracklistview.pluginspec \
    TrackListView.json

TRANSLATIONS += translations/TrackListView.zh_CN.ts

RESOURCES += \
    tracklistview.qrc
