#ifndef TESTDCMVR_H
#define TESTDCMVR_H

#include <QtTest/QtTest>
#include "DcmVr.h"

class TestDcmVr: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testVr()
    {
        DcmVr vr0;

        QVERIFY(vr0 == DcmVr::Invalid);

        vr0 = DcmVr::UI;

        QVERIFY(vr0 != DcmVr::Invalid);
        QVERIFY(vr0 == DcmVr(DcmVrKey_UI, 0, 64));
        QVERIFY(vr0.vrKey() == DcmVrKey_UI);
        QVERIFY(vr0.isString());
        QVERIFY(!vr0.isPadded());
        QVERIFY(!vr0.isBinary());
        QVERIFY(vr0.minSize() == 0);
        QVERIFY(vr0.maxSize() == 64);
        QVERIFY(vr0.toString() == "UI");

        DcmVr vr1 = DcmVr::FD;
        QVERIFY(vr0 != vr1);
        QVERIFY(vr1.vrKey() == DcmVrKey_FD);
        QVERIFY(vr1.minSize() == 8);
        QVERIFY(vr1.maxSize() == 8);
        QVERIFY(!vr1.isString());
        QVERIFY(!vr1.isBinary());
        QVERIFY(!vr1.isPadded());

        vr1 = DcmVr::CS;
        QVERIFY(vr1.isString());
        QVERIFY(vr1.isPadded());
        QVERIFY(vr1.vrKey() == DcmVrKey_CS);
        QVERIFY(vr1.minSize() == 0);
        QVERIFY(vr1.maxSize() == 16);
        QVERIFY(vr1.toString() == "CS");

        vr0 = DcmVr::fromString("CS");
        QVERIFY(vr0 == vr1);
    }

    void cleanupTestCase()
    {}

};

#endif // TESTDCMVR_H
