#-------------------------------------------------
#
# Project created by QtCreator 2018-12-22 10:28:13
#
#-------------------------------------------------


# add include pri file
include($$PWD/../QDcm_Multi.pri)

QT	 +=core network xml

TEMPLATE	 =lib

TARGET	 =dcmcore$${FILE_POSTFIX}

INCLUDEPATH +=$$PWD/include

SOURCES += \
    src/DcmCharSet.cpp \
    src/DcmDataset.cpp \
    src/DcmDictionary.cpp \
    src/DcmFile.cpp \
    src/DcmGlobal.cpp \
    src/DcmModule.cpp \
    src/DcmPDUItem.cpp \
    src/DcmReader.cpp \
    src/DcmStream.cpp \
    src/DcmTag.cpp \
    src/DcmTagAE.cpp \
    src/DcmTagAS.cpp \
    src/DcmTagAT.cpp \
    src/DcmTagBinary.cpp \
    src/DcmTagCS.cpp \
    src/DcmTagDA.cpp \
    src/DcmTagDescription.cpp \
    src/DcmTagDS.cpp \
    src/DcmTagDT.cpp \
    src/DcmTagFD.cpp \
    src/DcmTagFL.cpp \
    src/DcmTagGroup.cpp \
    src/DcmTagIS.cpp \
    src/DcmTagItem.cpp \
    src/DcmTagKey.cpp \
    src/DcmTagList.cpp \
    src/DcmTagLO.cpp \
    src/DcmTagLT.cpp \
    src/DcmTagPixelData.cpp \
    src/DcmTagPixelDataItem.cpp \
    src/DcmTagPN.cpp \
    src/DcmTagSH.cpp \
    src/DcmTagSL.cpp \
    src/DcmTagSQ.cpp \
    src/DcmTagSS.cpp \
    src/DcmTagST.cpp \
    src/DcmTagString.cpp \
    src/DcmTagTM.cpp \
    src/DcmTagUI.cpp \
    src/DcmTagUL.cpp \
    src/DcmTagUS.cpp \
    src/DcmTagUT.cpp \
    src/DcmTransferSyntax.cpp \
    src/DcmVr.cpp \
    src/DcmWriter.cpp

RESOURCES += \
    resources/dcmcore.qrc

