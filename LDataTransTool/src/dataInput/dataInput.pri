INCLUDEPATH +=\
    $$PWD/3rdparty \
    $$PWD/3rdparty/serialport/serialport_src \

include($$PWD/3rdparty/3rdparty.pri)

HEADERS += \
    $$PWD/readserialport.h \
    $$PWD/readfromtcpserver.h

SOURCES += \
    $$PWD/readserialport.cpp \
    $$PWD/readfromtcpserver.cpp
