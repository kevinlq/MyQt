TEMPLATE = app

QT += qml quick
QT  += xml svg

CONFIG += c++11

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = release/SVGPicOperator
        } else {
            target_path = build_/debug
            TARGET  = debug/SVGPicOperator
        }
        DESTDIR = $$PWD/Bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += $$PWD/Bin

SOURCES += main.cpp \
    svgparsedom.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    svgparsedom.h
