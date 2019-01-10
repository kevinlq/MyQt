#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22 10:28:13
#
#-------------------------------------------------


# add include pri file
include($$PWD/../QDcm_Multi.pri)

QT	 +=core widgets network xml

TEMPLATE = app

TARGET	 =dcmview

INCLUDEPATH +=$$PWD/include

INCLUDEPATH +=$$PWD/../dcmcore/include
INCLUDEPATH +=$$PWD/../dcmimage/include

SOURCES += \
    src/DicomTreeModel.cpp \
    src/DicomWindow.cpp \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    include/DicomTreeModel.h \
    include/DicomWindow.h \
    include/MainWindow.h

LIBS +=-L$${DIR_DEPEND_DEST} -ldcmcore$${FILE_POSTFIX}
LIBS +=-L$${DIR_DEPEND_DEST} -ldcmimage$${FILE_POSTFIX}

RESOURCES += \
    resources/dcmview.qrc
