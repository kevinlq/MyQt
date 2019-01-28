TEMPLATE = app
TARGET = RadarDisplay
include(../extensionsystem/extensionsystem.pri)
QT += gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += ../
DESTDIR = ../lib
LIBS += -L../lib
SOURCES += \
    main.cpp

win32 {
    RC_FILE = app.rc
    debug: OUT_SUBDIR = debug
    else: OUT_SUBDIR = release
}

app_install.files = $$DESTDIR/$${TARGET}.exe
app_install.path = $$(INSTALLDIR)
INSTALLS += app_install
