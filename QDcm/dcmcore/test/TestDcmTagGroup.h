#ifndef TESTDCMTAGGROUP_H
#define TESTDCMTAGGROUP_H

#include <QtTest/QtTest>
#include "DcmTagGroup.h"
#include "DcmTagCS.h"
#include "DcmTagUI.h"

class TestDcmTagGroup: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testTagGroup()
    {
        DcmTagGroup group0002(0x0002);

        QVERIFY(group0002.isGroup());
        QVERIFY(group0002.tagKey().group() == 0x0002);
        QVERIFY(group0002.tagKey().element() == 0x0000);
        QVERIFY(group0002.tags().count() == 0);
        QVERIFY(group0002.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 0);
        QVERIFY(group0002.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);

        DcmTagCS tagCs(DcmTagKey(0x0002, 0x0001));
        tagCs.setString("tag1");

        group0002.insert(tagCs);
        QVERIFY(group0002.tags().count() == 1);
        DcmTag *tag = group0002.findTag(DcmTagKey(0x0004, 0x0005));
        QVERIFY(tag == 0);
        tag = group0002.findTag(DcmTagKey(0x0002, 0x0001));
        QVERIFY(tag);
        QVERIFY(!tag->isGroup());
        QVERIFY(tag->tagKey() == DcmTagKey(0x0002, 0x0001));
        QVERIFY(tag->vr() == DcmVr::CS);
        QVERIFY(tag->value().toString() == "tag1");

        QVERIFY(group0002.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 12);
        QVERIFY(group0002.size(DcmTransferSyntax::ExplicitLittleEndian) == 24);

    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMTAGGROUP_H
