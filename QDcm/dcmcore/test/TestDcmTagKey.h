#ifndef TESTDCMTAGKEY_H
#define TESTDCMTAGKEY_H

#include <QtTest/QtTest>
#include "DcmTagKey.h"

class TestDcmTagKey: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testTagKey()
    {
        DcmTagKey key0;

        QVERIFY(key0.group() == 0);
        QVERIFY(key0.element() == 0);

        DcmTagKey key1(0x1234, 0x5678);

        QVERIFY(key1.group() == 0x1234);
        QVERIFY(key1.element() == 0x5678);

        QVERIFY(key0 != key1);
        QVERIFY(key0 < key1);
        QVERIFY(key0 <= key1);
        QVERIFY(key1 > key0);
        QVERIFY(key1 >= key0);
        QVERIFY(!(key0 == key1));

        key0.setGroup(0x1234);

        QVERIFY(key0.isGroupSize());
        QVERIFY(!key0.isPrivate());
        QVERIFY(!key1.isPrivate());
        QVERIFY(!key0.isAlwaysImplicit());
        QVERIFY(!key1.isAlwaysImplicit());

        QVERIFY(key0.toString() == "(1234, 0000)");
        QVERIFY(key1.toString() == "(1234, 5678)");

        QVERIFY(key0.hash() == 0x12340000);
        QVERIFY(key1.hash() == 0x12345678);

        key0 = 0x33336666;
        key1 = DcmTagKey(0x3333, 0x6666);

        QVERIFY(key0 == key1);
        QVERIFY(!(key0 != key1));
        QVERIFY(key0.group() == 0x3333);
        QVERIFY(key0.element() == 0x6666);
        QVERIFY(key0.isPrivate());
        QVERIFY(!key0.isGroupSize());

        QVERIFY(DcmTagKey::Item.isAlwaysImplicit());
        QVERIFY(DcmTagKey::ItemDeliminationItem.isAlwaysImplicit());
        QVERIFY(DcmTagKey::SequenceDeliminationItem.isAlwaysImplicit());
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMTAGKEY_H
