#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22 10:28:13
#
#-------------------------------------------------


# add include pri file
include($$PWD/../QDcm_Multi.pri)

QT	 +=core network xml

TEMPLATE	 =lib

TARGET	 =dcmnet$${FILE_POSTFIX}

INCLUDEPATH +=$$PWD/include
INCLUDEPATH +=$$PWD/../dcmcore/include
INCLUDEPATH +=$$PWD/../dcmimage/include


SOURCES += \
    $$PWD/cpp/DcmAAbort.cpp \
    $$PWD/cpp/DcmAAssociateAccept.cpp \
    $$PWD/cpp/DcmAAssociateReject.cpp \
    $$PWD/cpp/DcmAAssociateRequest.cpp \
    $$PWD/cpp/DcmAbstractSyntax.cpp \
    $$PWD/cpp/DcmAcceptedPresentationContext.cpp \
    $$PWD/cpp/DcmApplicationContext.cpp \
    $$PWD/cpp/DcmAReleaseRequest.cpp \
    $$PWD/cpp/DcmAReleaseResponse.cpp \
    $$PWD/cpp/DcmCEchoRequest.cpp \
    $$PWD/cpp/DcmCEchoResponse.cpp \
    $$PWD/cpp/DcmCommunicator.cpp \
    $$PWD/cpp/DcmDimseMessage.cpp \
    $$PWD/cpp/DcmDimsePriorityRequest.cpp \
    $$PWD/cpp/DcmDimseRequest.cpp \
    $$PWD/cpp/DcmDimseResponse.cpp \
    $$PWD/cpp/DcmNetStream.cpp \
    $$PWD/cpp/DcmPDataTf.cpp \
    $$PWD/cpp/DcmPDUImplementationClassUID.cpp \
    $$PWD/cpp/DcmPDUImplementationVersionName.cpp \
    $$PWD/cpp/DcmPDUItemList.cpp \
    $$PWD/cpp/DcmPDUMaxLength.cpp \
    $$PWD/cpp/DcmPDUUserInfo.cpp \
    $$PWD/cpp/DcmPDVItem.cpp \
    $$PWD/cpp/DcmPresentationContext.cpp \
    $$PWD/cpp/DcmSCU.cpp

HEADERS += \
    $$PWD/include/DcmAAbort.h \
    $$PWD/include/DcmAAssociateAccept.h \
    $$PWD/include/DcmAAssociateReject.h \
    $$PWD/include/DcmAAssociateRequest.h \
    $$PWD/include/DcmAbstractSyntax.h \
    $$PWD/include/DcmAcceptedPresentationContext.h \
    $$PWD/include/DcmApplicationContext.h \
    $$PWD/include/DcmAReleaseRequest.h \
    $$PWD/include/DcmAReleaseResponse.h \
    $$PWD/include/DcmCEchoRequest.h \
    $$PWD/include/DcmCEchoResponse.h \
    $$PWD/include/DcmCommunicator.h \
    $$PWD/include/DcmDimseMessage.h \
    $$PWD/include/DcmDimsePriorityRequest.h \
    $$PWD/include/DcmDimseRequest.h \
    $$PWD/include/DcmDimseResponse.h \
    $$PWD/include/DcmNetApi.h \
    $$PWD/include/DcmNetStream.h \
    $$PWD/include/DcmPDataTf.h \
    $$PWD/include/DcmPDUImplementationClassUID.h \
    $$PWD/include/DcmPDUImplementationVersionName.h \
    $$PWD/include/DcmPDUItemList.h \
    $$PWD/include/DcmPDUMaxLength.h \
    $$PWD/include/DcmPDUUserInfo.h \
    $$PWD/include/DcmPDVItem.h \
    $$PWD/include/DcmPresentationContext.h \
    $$PWD/include/DcmSCU.h


LIBS +=-L$${DIR_DEPEND_DEST} -ldcmcore$${FILE_POSTFIX}
LIBS +=-L$${DIR_DEPEND_DEST} -ldcmimage$${FILE_POSTFIX}
