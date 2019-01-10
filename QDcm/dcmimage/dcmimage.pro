#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22 10:28:13
#
#-------------------------------------------------


# add include pri file
include($$PWD/../QDcm_Multi.pri)

QT	 +=core network xml

TEMPLATE	 =lib

TARGET	 =dcmimage$${FILE_POSTFIX}

INCLUDEPATH +=$$PWD/include
INCLUDEPATH +=$$PWD/../dcmcore/include

SOURCES += \
    src/DcmImage.cpp \
    src/DcmImageTransferFunction.cpp \
    src/DcmMonochromeImage.cpp \
    src/DcmPhotometricInterpretation.cpp


LIBS +=-L$${DIR_DEPEND_DEST} -ldcmcore$${FILE_POSTFIX}
