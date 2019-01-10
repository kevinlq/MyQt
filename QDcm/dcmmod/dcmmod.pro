#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22 10:28:13
#
#-------------------------------------------------


# add include pri file
include($$PWD/../QDcm_Multi.pri)

QT	 +=core network xml

TEMPLATE	 =lib

TARGET	 =dcmmod$${FILE_POSTFIX}

INCLUDEPATH +=$$PWD/include
INCLUDEPATH +=$$PWD/../dcmcore/include
INCLUDEPATH +=$$PWD/../dcmimage/include

SOURCES += \
    src/DcmModuleGeneralEquipmentAttributes.cpp \
    src/DcmModulePatient.cpp \
    src/DcmModuleSOPCommon.cpp \
    src/DcmModuleStudy.cpp


LIBS +=-L$${DIR_DEPEND_DEST} -ldcmcore$${FILE_POSTFIX}
LIBS +=-L$${DIR_DEPEND_DEST} -ldcmimage$${FILE_POSTFIX}
