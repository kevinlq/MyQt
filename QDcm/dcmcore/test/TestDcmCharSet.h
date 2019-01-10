#ifndef TESTDCMCHARSET_H
#define TESTDCMCHARSET_H

#include <QtTest/QtTest>
#include "DcmCharSet.h"

class TestDcmCharSet: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testCharSets()
    {
        // Testing for available encodings.
        QVERIFY(DcmCharSet::forName("GB18030").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 6").isValid());
        //QVERIFY(DcmCharSet::forName("ISO_IR 13").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 100").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 101").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 109").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 110").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 126").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 127").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 138").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 144").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 148").isValid());
        //QVERIFY(DcmCharSet::forName("ISO_IR 166").isValid());
        QVERIFY(DcmCharSet::forName("ISO_IR 192").isValid());
        QVERIFY(DcmCharSet::forName("ISO_2022_IR 13").isValid());
        QVERIFY(DcmCharSet::forName("ISO_2022_IR 87").isValid());
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMCHARSET_H
