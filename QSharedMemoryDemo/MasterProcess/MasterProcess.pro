include($$PWD/../QSharedMemoryDemo.pri)

QT = core
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

TARGET = MasterP$${FILE_POSTFIX}
DESTDIR = $${IDE_BIN_PATH}


SOURCES += \
    main.cpp
