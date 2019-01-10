#ifndef TESTDCMTAGSEQUENCE_H
#define TESTDCMTAGSEQUENCE_H

#include <QtTest/QtTest>
#include "DcmTagSQ.h"
#include "DcmTagUI.h"

class TestDcmTagSequence: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testSequence()
    {
        DcmTagSQ sequence(DcmTagKey(0x0008, 0x1140));

        QVERIFY(sequence.items().count() == 0);
        QVERIFY(sequence.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 0);
        QVERIFY(sequence.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);
        QVERIFY(sequence.size(DcmTransferSyntax::ImplicitLittleEndian) == 8);

        DcmTagUI referenceUid(DcmTagKey(0x0008, 0x1150));
        referenceUid.setString("1.2.840.10008.5.1.4.1.1.2");
        QVERIFY(referenceUid.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 26);
        QVERIFY(referenceUid.size(DcmTransferSyntax::ExplicitLittleEndian) == 34);

        DcmTagUI instanceUid(DcmTagKey(0x0008, 0x1155));
        instanceUid.setString("1.2.840.113704.1.111.1068.1317049597.2140");
        QVERIFY(instanceUid.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 42);
        QVERIFY(instanceUid.size(DcmTransferSyntax::ExplicitLittleEndian) == 50);

        DcmTagItem item;
        item.insert(referenceUid);

        // Add 12 for group tag
        QVERIFY(item.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 34 + 12);

        item.insert(instanceUid);
        QVERIFY(item.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 50 + 34 + 12);

        QVERIFY(item.size(DcmTransferSyntax::ExplicitLittleEndian) == 50 + 34 + 12 + 8);

        sequence.insert(item);

        QVERIFY(sequence.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 50 + 34 + 12 + 8);
        QVERIFY(sequence.size(DcmTransferSyntax::ExplicitLittleEndian) == 50 + 34 + 12 + 8 + 12);

    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMTAGSEQUENCE_H
