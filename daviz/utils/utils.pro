TEMPLATE = lib
TARGET = Utils
DEFINES += UTILS_LIBRARY

QT += core gui opengl
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 3d
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../davizlib.pri)

HEADERS += \
    fancytabwidget.h \
    fancyheaderview.h \
    utils_global.h \
    utilstranslation.h \
    separatorwidget.h \
    rangebar.h \
    textitem.h \
    selectionitem.h

#greaterThan(QT_MAJOR_VERSION, 4): HEADERS += qglgraphicsviewportitem.h

SOURCES += \
    fancytabwidget.cpp \
    fancyheaderview.cpp \
    utilstranslation.cpp \
    separatorwidget.cpp \
    rangebar.cpp \
    textitem.cpp \
    selectionitem.cpp

#greaterThan(QT_MAJOR_VERSION, 4): SOURCES += qglgraphicsviewportitem.cpp

TRANSLATIONS += translations/utils.zh_CN.ts

OTHER_FILES += \
    utils.pri

RESOURCES += \
    utils.qrc
