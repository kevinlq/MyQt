TEMPLATE = lib
TARGET = ExtensionSystem
DEFINES += EXTENSIONSYSTEM_LIBRARY

greaterThan(QT_MAJOR_VERSION, 4): QT += gui widgets

include(../davizlib.pri)

unix:!macx:!freebsd*:LIBS += -ldl

HEADERS += pluginerrorview.h \
    plugindetailsview.h \
    invoker.h \
    iplugin.h \
    iplugin_p.h \
    extensionsystem_global.h \
    pluginmanager.h \
    pluginmanager_p.h \
    pluginspec.h \
    pluginspec_p.h \
    pluginview.h \
    optionsparser.h \
    plugincollection.h \
    pluginerroroverview.h \
    aggregate.h
SOURCES += pluginerrorview.cpp \
    plugindetailsview.cpp \
    invoker.cpp \
    iplugin.cpp \
    pluginmanager.cpp \
    pluginspec.cpp \
    pluginview.cpp \
    optionsparser.cpp \
    plugincollection.cpp \
    pluginerroroverview.cpp \
    aggregate.cpp
FORMS += pluginview.ui \
    pluginerrorview.ui \
    plugindetailsview.ui \
    pluginerroroverview.ui
RESOURCES += pluginview.qrc

TRANSLATIONS += translations/ExtensionSystem.zh_CN.ts
