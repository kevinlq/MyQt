HEADERS +=\
        $$PWD/serialport_src/qextserialport_global.h \
        $$PWD/serialport_src/qextserialport.h
SOURCES +=\
    $$PWD/serialport_src/qextserialport.cpp

win32 {
     SOURCES += $$PWD/serialport_src/qextserialport_win.cpp
}

unix {
     SOURCES += $$PWD/serialport_src/qextserialport_unix.cpp
}
