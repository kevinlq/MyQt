#ifndef TESTDCMTAGS_H
#define TESTDCMTAGS_H

#include <QtTest/QtTest>
#include "DcmTagSS.h"
#include "DcmTagUS.h"
#include "DcmTagDS.h"
#include "DcmTagSL.h"
#include "DcmTagUL.h"
#include "DcmTagAT.h"
#include "DcmTagFL.h"
#include "DcmTagFD.h"
#include "DcmTagList.h"
#include "DcmTransferSyntax.h"

class TestDcmTags: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testTagSS()
    {
        DcmTagSS t0;

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::SS);

        DcmTagSS t1(DcmTagKey(0x1234, 0x5678));
        QVERIFY(t1.tagKey().group() == 0x1234);
        QVERIFY(t1.tagKey().element() == 0x5678);
        QVERIFY(t1.vr() == DcmVr::SS);
        QVERIFY(t1.multiplicity() == 0);
        QVERIFY(!t1.value().isValid());

        t1.appendSignedShort(123);
        QVERIFY(t1.multiplicity() == 1);
        QVERIFY(t1.value().toInt() == 123);
        QVERIFY(t1.asSignedShort() == 123);
        QVariantList values = t1.values();
        QVERIFY(values.count() == 1);
        QVERIFY(values.at(0).toInt() == 123);
        QList<DcmSignedShort> ssValues = t1.asSignedShortList();
        QVERIFY(ssValues.count() == 1);
        QVERIFY(ssValues.at(0) == 123);

        t1.appendSignedShort(-456);
        QVERIFY(t1.multiplicity() == 2);
        QVERIFY(t1.value().toInt() == 123);
        QVERIFY(t1.asSignedShort() == 123);
        values = t1.values();
        QVERIFY(values.count() == 2);
        QVERIFY(values.at(0).toInt() == 123);
        QVERIFY(values.at(1).toInt() == -456);
        ssValues = t1.asSignedShortList();
        QVERIFY(ssValues.count() == 2);
        QVERIFY(ssValues.at(0) == 123);
        QVERIFY(ssValues.at(1) == -456);

        QVERIFY(t1.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 4);
        QVERIFY(t1.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);
    }

    void testTagUS()
    {
        DcmTagUS t0;

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::US);

        DcmTagUS t1(DcmTagKey(0x1234, 0x5678));
        QVERIFY(t1.tagKey().group() == 0x1234);
        QVERIFY(t1.tagKey().element() == 0x5678);
        QVERIFY(t1.vr() == DcmVr::US);
        QVERIFY(t1.multiplicity() == 0);
        QVERIFY(!t1.value().isValid());

        t1.appendUnsignedShort(123);
        QVERIFY(t1.multiplicity() == 1);
        QVERIFY(t1.value().toUInt() == 123);
        QVERIFY(t1.asUnsignedShort() == 123);
        QVariantList values = t1.values();
        QVERIFY(values.count() == 1);
        QVERIFY(values.at(0).toUInt() == 123);
        QList<DcmUnsignedShort> usValues = t1.asUnsignedShortList();
        QVERIFY(usValues.count() == 1);
        QVERIFY(usValues.at(0) == 123);

        t1.appendUnsignedShort(456);
        QVERIFY(t1.multiplicity() == 2);
        QVERIFY(t1.value().toUInt() == 123);
        QVERIFY(t1.asUnsignedShort() == 123);
        values = t1.values();
        QVERIFY(values.count() == 2);
        QVERIFY(values.at(0).toUInt() == 123);
        QVERIFY(values.at(1).toUInt() == 456);
        usValues = t1.asUnsignedShortList();
        QVERIFY(usValues.count() == 2);
        QVERIFY(usValues.at(0) == 123);
        QVERIFY(usValues.at(1) == 456);

        QVERIFY(t1.contentSize(DcmTransferSyntax::ExplicitBigEndian) == 4);
        QVERIFY(t1.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);
    }

    void testTagDS()
    {
        DcmTagDS t0;

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::DS);

        DcmTagDS t1(DcmTagKey(0x1234, 0x5678));
        QVERIFY(t1.tagKey().group() == 0x1234);
        QVERIFY(t1.tagKey().element() == 0x5678);

        QVERIFY(t1.contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 0);
        t1.appendDouble(0);
        QVERIFY(t1.contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 2);
        QVERIFY(t1.size(DcmTransferSyntax::ImplicitLittleEndian) == 10);
        t1.appendDouble(1);
        QVERIFY(t1.contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 4);
        QVERIFY(t1.size(DcmTransferSyntax::ImplicitLittleEndian) == 12);

        QVariantList values = t1.values();
        QVERIFY(values.count() == 2);
        QVERIFY(values.at(0).toDouble() == 0.0);
        QVERIFY(values.at(1).toDouble() == 1.0);

        DcmTag *pTag = DcmTag::create(DcmTagKey(0x300b, 0x1018));
        QVERIFY(pTag);
        QVERIFY(pTag->vr() == DcmVr::DS);
        pTag->setValue(4.5);
        DcmTagDS *pTagDs = dynamic_cast<DcmTagDS*>(pTag);
        QVERIFY(pTagDs);
        QVERIFY(pTagDs->asDouble() == 4.5);

        QVERIFY(pTag->contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 4);
        QVERIFY(pTag->size(DcmTransferSyntax::ImplicitLittleEndian) == 12);

        delete pTag;
    }

    void testTagSL()
    {
        DcmTagSL t0;

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::SL);

        DcmTagSL t1(DcmTagKey(0x1234, 0x5678));
        QVERIFY(t1.tagKey().group() == 0x1234);
        QVERIFY(t1.tagKey().element() == 0x5678);
        QVERIFY(t1.vr() == DcmVr::SL);
        QVERIFY(t1.multiplicity() == 0);
        QVERIFY(!t1.value().isValid());

        t1.appendSignedLong(123);
        QVERIFY(t1.multiplicity() == 1);
        QVERIFY(t1.value().toInt() == 123);
        QVERIFY(t1.asSignedLong() == 123);
        QVariantList values = t1.values();
        QVERIFY(values.count() == 1);
        QVERIFY(values.at(0).toInt() == 123);
        QList<DcmSignedLong> slValues = t1.asSignedLongList();
        QVERIFY(slValues.count() == 1);
        QVERIFY(slValues.at(0) == 123);

        t1.appendSignedLong(-456);
        QVERIFY(t1.multiplicity() == 2);
        QVERIFY(t1.value().toInt() == 123);
        QVERIFY(t1.asSignedLong() == 123);
        values = t1.values();
        QVERIFY(values.count() == 2);
        QVERIFY(values.at(0).toInt() == 123);
        QVERIFY(values.at(1).toInt() == -456);
        slValues = t1.asSignedLongList();
        QVERIFY(slValues.count() == 2);
        QVERIFY(slValues.at(0) == 123);
        QVERIFY(slValues.at(1) == -456);

        QVERIFY(t1.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 8);
        QVERIFY(t1.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);
    }

    void testTagUL()
    {
        DcmTagUL t0;

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::UL);

        DcmTagUL t1(DcmTagKey(0x1234, 0x5678));
        QVERIFY(t1.tagKey().group() == 0x1234);
        QVERIFY(t1.tagKey().element() == 0x5678);
        QVERIFY(t1.vr() == DcmVr::UL);
        QVERIFY(t1.multiplicity() == 0);
        QVERIFY(!t1.value().isValid());

        t1.appendUnsignedLong(123);
        QVERIFY(t1.multiplicity() == 1);
        QVERIFY(t1.value().toUInt() == 123);
        QVERIFY(t1.asUnsignedLong() == 123);
        QVariantList values = t1.values();
        QVERIFY(values.count() == 1);
        QVERIFY(values.at(0).toUInt() == 123);
        QList<DcmUnsignedLong> ulValues = t1.asUnsignedLongList();
        QVERIFY(ulValues.count() == 1);
        QVERIFY(ulValues.at(0) == 123);

        t1.appendUnsignedLong(456);
        QVERIFY(t1.multiplicity() == 2);
        QVERIFY(t1.value().toUInt() == 123);
        QVERIFY(t1.asUnsignedLong() == 123);
        values = t1.values();
        QVERIFY(values.count() == 2);
        QVERIFY(values.at(0).toUInt() == 123);
        QVERIFY(values.at(1).toUInt() == 456);
        ulValues = t1.asUnsignedLongList();
        QVERIFY(ulValues.count() == 2);
        QVERIFY(ulValues.at(0) == 123);
        QVERIFY(ulValues.at(1) == 456);

        QVERIFY(t1.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 8);
        QVERIFY(t1.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);
    }

    void testTagAT()
    {
        DcmTagAT t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::AT);
        QVERIFY(t0.tagKey().group() == 0x1234);
        QVERIFY(t0.tagKey().element() == 0x5678);
        QVERIFY(t0.multiplicity() == 0);
        QVERIFY(!t0.value().isValid());

        t0.setValue(t0.tagKey().hash());
        QVERIFY(t0.multiplicity() == 1);
        QVERIFY(t0.value().toUInt() == t0.tagKey().hash());
        QVERIFY(DcmTagKey(t0.value().toUInt()) == t0.tagKey());

        DcmTagKey key(0x3333, 0x7777);
        t0.appendValue(key.hash());
        QVERIFY(t0.multiplicity() == 2);
        QVariantList values = t0.values();

        QVERIFY(values.at(0).toUInt() == t0.tagKey().hash());
        QVERIFY(values.at(1).toUInt() == key.hash());

        QList<DcmTagKey> tkValues = t0.asDcmTagKeyList();
        QVERIFY(tkValues.count() == 2);
        QVERIFY(tkValues.at(0) == t0.tagKey());
        QVERIFY(tkValues.at(1) == key);

        QVERIFY(t0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 8);
        QVERIFY(t0.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);
    }

    void testTagFL()
    {
        DcmTagFL t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::FL);
        QVERIFY(t0.tagKey().group() == 0x1234);
        QVERIFY(t0.tagKey().element() == 0x5678);
        QVERIFY(t0.multiplicity() == 0);
        QVERIFY(!t0.value().isValid());

        t0.setValue(0.125f);
        QVERIFY(t0.multiplicity() == 1);
        QVERIFY(t0.value().toFloat() == 0.125f);
        QVERIFY(t0.asFloat() == 0.125f);

        QVariantList values = t0.values();
        QVERIFY(values.count() == 1);
        QVERIFY(values.at(0).toFloat() == 0.125f);

        t0.appendFloat(0.5);
        QVERIFY(t0.multiplicity() == 2);
        QList<DcmFloat> flValues = t0.asFloatList();
        QVERIFY(flValues.count() == 2);
        QVERIFY(flValues.at(0) == 0.125f);
        QVERIFY(flValues.at(1) == 0.5f);

        QVERIFY(t0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 8);
        QVERIFY(t0.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);
    }

    void testTagFD()
    {
        DcmTagFD t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.isValid());
        QVERIFY(t0.vr() == DcmVr::FD);
        QVERIFY(t0.tagKey().group() == 0x1234);
        QVERIFY(t0.tagKey().element() == 0x5678);
        QVERIFY(t0.multiplicity() == 0);
        QVERIFY(!t0.value().isValid());

        t0.setValue(0.125);
        QVERIFY(t0.multiplicity() == 1);
        QVERIFY(t0.value().toDouble() == 0.125);
        QVERIFY(t0.asDouble() == 0.125);

        QVariantList values = t0.values();
        QVERIFY(values.count() == 1);
        QVERIFY(values.at(0).toDouble() == 0.125);

        QVERIFY(t0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 8);
        QVERIFY(t0.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);

        t0.appendDouble(0.5);
        QVERIFY(t0.multiplicity() == 2);
        QList<DcmDouble> fdValues = t0.asDoubleList();
        QVERIFY(fdValues.count() == 2);
        QVERIFY(fdValues.at(0) == 0.125);
        QVERIFY(fdValues.at(1) == 0.5);

        QVERIFY(t0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 16);
        QVERIFY(t0.size(DcmTransferSyntax::ExplicitLittleEndian) == 24);
    }

    void testTagList()
    {
        DcmTagList tagList;

        QVERIFY(tagList.count() == 0);
        QVERIFY(tagList.findFirst(DcmTagKey(0x1234, 0x5678)) == 0);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 0);

        DcmTagSS tagSS(DcmTagKey(0x1000, 0x2000));
        tagSS.setSignedShort(123);
        tagList.insert(tagSS);
        QVERIFY(tagList.count() == 1);
        QVERIFY(tagList.findFirst(DcmTagKey(0x1000, 0x2000)) != 0);
        QVERIFY(tagList.findFirst(DcmTagKey(0x1000, 0x2000))->value().toInt() == 123);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 10);

        tagList.insert(tagSS);
        QVERIFY(tagList.count() == 2);

        tagSS.setValue(567);
        tagList.insertOrReplace(tagSS);
        QVERIFY(tagList.count() == 2);
        QVERIFY(tagList.findFirst(DcmTagKey(0x1000, 0x2000))->value().toInt() == 567);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 20);

        DcmTagFL tagFL(DcmTagKey(0x2000, 0x3000));
        tagFL.setFloat(0.125);
        tagList.insert(tagFL);

        QVERIFY(tagList.count() == 3);
        QVERIFY(tagList.findFirst(DcmTagKey(0x2000, 0x3000))->value().toFloat() == 0.125);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 32);

        tagList.removeFirst(DcmTagKey(0x1000, 0x2000));
        QVERIFY(tagList.count() == 2);
        QVERIFY(tagList.findFirst(DcmTagKey(0x1000, 0x2000))->value().toInt() == 123);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 22);

        tagList.removeAll(DcmTagKey(0x1000, 0x2000));
        QVERIFY(tagList.count() == 1);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);

        tagList.clear();
        QVERIFY(tagList.count() == 0);
        QVERIFY(tagList.size(DcmTransferSyntax::ExplicitLittleEndian) == 0);
    }

    void testTagsCreate()
    {
        DcmTag *tagPatientName = DcmTag::create("patientName");
        QVERIFY(tagPatientName);
        QVERIFY(tagPatientName->tagKey() == DcmTagKey(0x0010, 0x0010));
        QVERIFY(tagPatientName->vr() == DcmVr::PN);
        delete tagPatientName;

        DcmTag *tagSyntax = DcmTag::create(DcmTagKey::TransferSyntaxUID);
        QVERIFY(tagSyntax);
        QVERIFY(tagSyntax->tagKey() == DcmTagKey::TransferSyntaxUID);
        QVERIFY(tagSyntax->vr() == DcmVr::UI);
        delete tagSyntax;
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMTAGS_H
