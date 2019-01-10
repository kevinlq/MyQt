#ifndef TESTDCMTRANSFERSYNTAX_H
#define TESTDCMTRANSFERSYNTAX_H

#include <QtTest/QtTest>
#include "DcmTransferSyntax.h"

class TestDcmTransferSyntax: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testTransferSyntax()
    {
        DcmTransferSyntax invalidTransferSyntax;

        QVERIFY(invalidTransferSyntax.type() == DcmPDUType_TransferSyntax);
        QVERIFY(!invalidTransferSyntax.isValid());

        DcmTransferSyntax invalidUidSyntax("aaa.bbb.ccc");
        QVERIFY(!invalidUidSyntax.isValid());

        DcmTransferSyntax validTransferSyntax("1.2.840.10008.1.2.2", DcmEndianess_BigEndian, DcmEncoding_Explicit);

        QVERIFY(validTransferSyntax.type() == DcmPDUType_TransferSyntax);
        QVERIFY(validTransferSyntax.uid() == "1.2.840.10008.1.2.2");
        QVERIFY(validTransferSyntax.endianess() == DcmEndianess_BigEndian);
        QVERIFY(validTransferSyntax.encoding() == DcmEncoding_Explicit);
        QVERIFY(validTransferSyntax.isValid());

        QVERIFY(validTransferSyntax == DcmTransferSyntax::ExplicitBigEndian);
    }

    void testTransferSyntaxFromUid()
    {
        DcmTransferSyntax ts = DcmTransferSyntax::fromUid(DcmTransferSyntax::ImplicitLittleEndian.uid());
        QVERIFY(ts == DcmTransferSyntax::ImplicitLittleEndian);

        ts = DcmTransferSyntax::fromUid(DcmTransferSyntax::ExplicitLittleEndian.uid());
        QVERIFY(ts == DcmTransferSyntax::ExplicitLittleEndian);

        ts = DcmTransferSyntax::fromUid(DcmTransferSyntax::ExplicitBigEndian.uid());
        QVERIFY(ts == DcmTransferSyntax::ExplicitBigEndian);

        ts = DcmTransferSyntax::fromUid(DcmTransferSyntax::JPEG2000Lossless.uid());
        QVERIFY(ts == DcmTransferSyntax::JPEG2000Lossless);
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMTRANSFERSYNTAX_H
