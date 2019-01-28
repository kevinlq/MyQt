#-------------------------------------------------
#
# Project created by QtCreator 2012-08-01T22:58:16
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = Replay

include(../../davizplugin.pri)
include(../core/core.pri)

DEFINES += REPLAY_LIBRARY
QT       += core gui network widgets

SOURCES += \
    replayplugin.cpp \
    recorder.cpp \
    recordreplaywidget.cpp \
    replayradar.cpp \
    replaywidget.cpp \
    recordwidget.cpp \
    replayslider.cpp

HEADERS  += \
    replayplugin.h \
    replay_global.h \
    recorder.h \
    recordtypes.h \
    recordreplaywidget.h \
    replayradar.h \
    recordwidget.h \
    replaywidget.h \
    replayconstants.h \
    replayslider.h

INCLUDEPATH += $(QS_ROOT)/xxpoint \
    $(QS_ROOT)/xxtrack \
	$$PWD/../core

OTHER_FILES += \
    replay.pluginspec \
    Replay.json

TRANSLATIONS += \
    translations/Replay.zh_CN.ts

RESOURCES += \
    replay.qrc
