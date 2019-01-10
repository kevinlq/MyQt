#ifndef TESTDCMDICTIONARY_H
#define TESTDCMDICTIONARY_H

#include <QtTest/QtTest>
#include "DcmDictionary.h"

class TestDcmDictionary : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}


#if 0
    void testDCMTK2XML()
    {
        // That is how we import DCMTK dictionary and save it in XML format
        QString pathDCMTK =
#ifdef WIN32
        "C:\\bin\\dcmtk-vs\\share\\dcmtk\\dicom.dic";
#else
        "/usr/local/share/dcmtk/dicom.dic";
#endif

        QString pathXML = "dicom.xml";

        DcmDictionary dictionary;
        dictionary.populateFromDCMTK(pathDCMTK);
        dictionary.dumpToXML(pathXML);
    }
#endif

    void testResourcesDictionary()
    {
        DcmDictionary dict;

        dict.populateFromXML(":/dcmcore/dicom.xml");

        DcmTagDescription tagDesc = dict.findByTagKey(DcmTagKey(0x0010, 0x0010));
        QVERIFY(tagDesc.isValid());
        QVERIFY(tagDesc.name() == "PatientName");
        QVERIFY(tagDesc.vr() == DcmVr::PN);
        QVERIFY(tagDesc.vmMin() == 1);
        QVERIFY(tagDesc.vmMax() == 1);
        QVERIFY(tagDesc.vmMod() == 1);

        tagDesc = dict.findByTagKey(DcmTagKey(0x0008, 0x1162));
        QVERIFY(tagDesc.isValid());
        QVERIFY(tagDesc.name() == "CalculatedFrameList");
        QVERIFY(tagDesc.vr() == DcmVr::UL);
        QVERIFY(tagDesc.vmMin() == 3);
        QVERIFY(tagDesc.vmMax() == DcmMultiplicity_Unknown);
        QVERIFY(tagDesc.vmMod() == 3);
    }

    void testDictionaryInstance()
    {
        DcmDictionary *dict1 = DcmDictionary::getInstancePtr();

        DcmTagDescription tagDesc = dict1->findByTagKey(DcmTagKey(0x0010, 0x0010));
        QVERIFY(tagDesc.isValid());
        QVERIFY(tagDesc.name() == "PatientName");
        QVERIFY(tagDesc.vr() == DcmVr::PN);
        QVERIFY(tagDesc.vmMin() == 1);
        QVERIFY(tagDesc.vmMax() == 1);
        QVERIFY(tagDesc.vmMod() == 1);

        DcmDictionary* dict2 = DcmDictionary::getInstancePtr();
        tagDesc = dict2->findByTagKey(DcmTagKey(0x0008, 0x1162));
        QVERIFY(tagDesc.isValid());
        QVERIFY(tagDesc.name() == "CalculatedFrameList");
        QVERIFY(tagDesc.vr() == DcmVr::UL);
        QVERIFY(tagDesc.vmMin() == 3);
        QVERIFY(tagDesc.vmMax() == DcmMultiplicity_Unknown);
        QVERIFY(tagDesc.vmMod() == 3);

        QVERIFY(dict1 == dict2);
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMDICTIONARY_H
