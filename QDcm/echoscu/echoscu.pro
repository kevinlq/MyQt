#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22 10:28:13
#
#-------------------------------------------------


# add include pri file
include($$PWD/../QDcm_Multi.pri)

QT	 +=core widgets network xml

TEMPLATE = app

TARGET	 =echoscu

INCLUDEPATH +=$$PWD/include

INCLUDEPATH +=$$PWD/../dcmcore/include
INCLUDEPATH +=$$PWD/../dcmimage/include
INCLUDEPATH +=$$PWD/../dcmnet/include

SOURCES += \
    $$PWD/cpp/CEchoSCU.cpp \
    $$PWD/cpp/main.cpp

HEADERS += \
    $$PWD/include/CEchoSCU.h


LIBS +=-L$${DIR_DEPEND_DEST} -ldcmcore$${FILE_POSTFIX}
LIBS +=-L$${DIR_DEPEND_DEST} -ldcmimage$${FILE_POSTFIX}
LIBS +=-L$${DIR_DEPEND_DEST} -ldcmnet$${FILE_POSTFIX}
