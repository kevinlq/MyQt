#ifndef TESTDCMTAGSTRING_H
#define TESTDCMTAGSTRING_H

#include <QtTest/QtTest>
#include "DcmGlobal.h"
#include "DcmTagString.h"
#include "DcmTagCS.h"
#include "DcmTagSH.h"
#include "DcmTagLO.h"
#include "DcmTagST.h"
#include "DcmTagLT.h"
#include "DcmTagUT.h"
#include "DcmTagAE.h"
#include "DcmTagPN.h"
#include "DcmTagUI.h"
#include "DcmTagDA.h"
#include "DcmTagTM.h"
#include "DcmTagDT.h"
#include "DcmTagAS.h"
#include "DcmTagIS.h"
#include "DcmTagDS.h"
#include "DcmTransferSyntax.h"

class TestDcmTagString: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testTagString()
    {
        DcmTagKey tagKey(0x1234, 0x5678);
        DcmTagString ts0(tagKey, DcmVr::DS);

        QVERIFY(ts0.tagKey() == tagKey);
        QVERIFY(ts0.vr() == DcmVr::DS);

        QString value0 = "1.234";
        QString value1 = "1\\2\\3\\4";

        ts0.setValue(QVariant(value0));
        QVERIFY(ts0.value().toString() == value0);
        QVERIFY(ts0.asString() == value0);
        QVERIFY(ts0.multiplicity() == 1);
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 6);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 14);

        ts0.setString(value1);
        QVERIFY(ts0.asString() == value1);
        QVERIFY(ts0.multiplicity() == 4);
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 8);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);

        QStringList sl = ts0.asStringList();
        QVERIFY(sl.size() == 4);
        QVERIFY(sl.at(0) == "1");
        QVERIFY(sl.at(1) == "2");
        QVERIFY(sl.at(2) == "3");
        QVERIFY(sl.at(3) == "4");

        QStringList list;
        list.append("1.23");
        list.append("3.45");

        ts0.setStringList(list);
        QVERIFY(ts0.multiplicity() == 2);
        QVERIFY(ts0.asString() == "1.23\\3.45");
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 10);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 18);

        ts0.setString("");
        QVERIFY(ts0.asString().isEmpty());
        QVERIFY(ts0.multiplicity() == 0);
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 0);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 8);

        ts0.appendValue(QString("5.67 "));
        QVERIFY(ts0.asString() == "5.67");
        QVERIFY(ts0.multiplicity() == 1);
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 4);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);
        ts0.appendString("  3.891");
        QVERIFY(ts0.asString() == "5.67\\3.891");
        QVERIFY(ts0.multiplicity() == 2);
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 10);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 18);

        ts0.setString("  text   ");
        QVERIFY(ts0.asString() == "text");
        QVERIFY(ts0.contentSize(DcmTransferSyntax::ExplicitLittleEndian) == 4);
        QVERIFY(ts0.size(DcmTransferSyntax::ExplicitLittleEndian) == 12);

        QVERIFY(ts0.isValid());
        ts0 = DcmTagString();
        QVERIFY(!ts0.isValid());
    }

    void testTagCS()
    {
        DcmTagCS t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::CS);
        QVERIFY(t0.tagKey().group() == 0x1234);
        QVERIFY(t0.tagKey().element() == 0x5678);
        QVERIFY(t0.multiplicity() == 0);

        t0.appendValue(QString(" code_123  "));
        QVERIFY(t0.multiplicity() == 1);
        QVERIFY(t0.value().toString() == "CODE_123");

        DcmTag *t = t0.clone();
        QVERIFY(t->tagKey().group() == 0x1234);
        QVERIFY(t->tagKey().element() == 0x5678);
        QVERIFY(t->vr() == DcmVr::CS);
        QVERIFY(t->value().toString() == "CODE_123");
        QVERIFY(t->contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 8);
        QVERIFY(t->size(DcmTransferSyntax::ImplicitLittleEndian) == 16);
    }

    void testTagSH()
    {
        DcmTagSH t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::SH);
        QVERIFY(t0.asString().isEmpty());

        t0.appendString(" some text  ");
        QVERIFY(t0.asString() == "some text");
        QVERIFY(t0.contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 10);
        QVERIFY(t0.size(DcmTransferSyntax::ImplicitLittleEndian) == 18);
    }

    void testTagLO()
    {
        DcmTagLO t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::LO);
    }

    void testTagST()
    {
        DcmTagST t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::ST);
    }

    void testTagLT()
    {
        DcmTagLT t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::LT);
    }

    void testTagUT()
    {
        DcmTagUT t0(DcmTagKey(0x1234, 0x5678));

        t0.setString("1234");

        QVERIFY(t0.vr() == DcmVr::UT);

        QVERIFY(t0.size(DcmTransferSyntax::ExplicitLittleEndian) == 16);
        QVERIFY(t0.size(DcmTransferSyntax::ImplicitLittleEndian) == 12);
    }

    void testTagAE()
    {
        DcmTagAE t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::AE);
    }

    void testTagPN()
    {
        DcmTagPN t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::PN);
    }

    void testTagUI()
    {
        DcmTagUI t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::UI);

        QVERIFY(dcmIsValidUID("1.2.3.4.5.6.7.8"));
        QVERIFY(!dcmIsValidUID("1. 2.4.5"));
        QVERIFY(dcmIsValidUID("123443"));
        QVERIFY(dcmIsValidUID(""));
        QVERIFY(!dcmIsValidUID("text"));

        t0.setValue("1.2.3.4.5");
        QVERIFY(t0.multiplicity() == 1);
        QVERIFY(t0.contentSize(DcmTransferSyntax::ImplicitLittleEndian) == 10);
        QVERIFY(t0.size(DcmTransferSyntax::ExplicitLittleEndian) == 18);
    }

    void testTagDA()
    {
        DcmTagDA t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::DA);
        t0.setDate(QDate(2012, 3, 8));

        QVERIFY(t0.value().toString() == "20120308");
        QVERIFY(t0.asDate() == QDate(2012, 3, 8));

        QVERIFY(dcmIsValidDateString("19480329"));
        QVERIFY(!dcmIsValidDateString("20112018"));
        QVERIFY(!dcmIsValidDateString("19991246"));
        QVERIFY(!dcmIsValidDateString("19981304"));
        QVERIFY(!dcmIsValidDateString("20000135"));

        t0.setValue(QString("19900101\\20121212"));
        QList<QDate> dl = t0.asDatesList();
        QVERIFY(dl.size() == 2);
        QVERIFY(dl.at(0) == QDate(1990, 1, 1));
        QVERIFY(dl.at(1) == QDate(2012, 12, 12));
        QVERIFY(t0.contentSize(DcmTransferSyntax::ExplicitBigEndian) == 18);
        QVERIFY(t0.size(DcmTransferSyntax::ExplicitBigEndian) == 26);
    }

    void testTagTM()
    {
        DcmTagTM t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::TM);
        t0.setTime(QTime(12, 45, 39, 18));

        QVERIFY(t0.value().toString() == "124539.018");
        QVERIFY(t0.asTime() == QTime(12, 45, 39, 18));

        t0.setValue(QString("051610"));
        QVERIFY(t0.asTime() == QTime(5, 16, 10));

        t0.setValue(QString("153000.100\\120516"));
        QList<QTime> tl = t0.asTimeList();
        QVERIFY(tl.size() == 2);
        QVERIFY(tl.at(0) == QTime(15, 30, 0, 100));
        QVERIFY(tl.at(1) == QTime(12, 5, 16));

        t0.setValue(QString("183200.00"));
        QVERIFY(t0.asTime() == QTime(18, 32, 0, 0));
    }

    void testTagDT()
    {
        DcmTagDT t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::DT);
        QDateTime dt(QDate(2012, 12, 12), QTime(12, 45, 39, 18));
        t0.setDateTime(dt);

        QVERIFY(t0.value().toString() == "20121212124539.018");
        QVERIFY(t0.asDateTime() == dt);

        t0.setValue(QString("19900315153000.100\\19970716120516"));
        QVERIFY(t0.multiplicity() == 2);
        QList<QDateTime> dtl = t0.asDateTimeList();
        QVERIFY(dtl.size() == 2);
        QVERIFY(dtl.at(0) == QDateTime(QDate(1990, 03, 15), QTime(15, 30, 0, 100)));
        QVERIFY(dtl.at(1) == QDateTime(QDate(1997, 07, 16), QTime(12, 5, 16)));
    }

    void testTagAS()
    {
        DcmTagAS t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::AS);
        t0.setValue(QString("033Y"));
        QVERIFY(t0.value().toString() == "033Y");

        QVERIFY(dcmIsValidAgeString("001D"));
        QVERIFY(dcmIsValidAgeString("012W"));
        QVERIFY(dcmIsValidAgeString("120M"));
        QVERIFY(dcmIsValidAgeString("300Y"));

        QVERIFY(!dcmIsValidAgeString("1Y"));
        QVERIFY(!dcmIsValidAgeString("23W"));
        QVERIFY(!dcmIsValidAgeString("123R"));
        QVERIFY(!dcmIsValidAgeString("123"));
    }

    void testTagIS()
    {
        DcmTagIS t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::IS);
        t0.setValue(12345);
        QVERIFY(t0.value().toString() == "12345");
        QVERIFY(t0.asInt() == 12345);

        t0.setValue("123\\567");
        QVERIFY(t0.multiplicity() == 2);
        QList<int> il = t0.asIntList();
        QVERIFY(il.size() == 2);
        QVERIFY(il.at(0) == 123);
        QVERIFY(il.at(1) == 567);
    }

    void testTagDS()
    {
        DcmTagDS t0(DcmTagKey(0x1234, 0x5678));

        QVERIFY(t0.vr() == DcmVr::DS);
        t0.setValue(0.125);
        QVERIFY(t0.value().toString() == "0.125");
        QVERIFY(t0.asDouble() == 0.125);

        t0.setValue("2.5\\-0.125\\13");
        QVERIFY(t0.multiplicity() == 3);
        QList<double> dl = t0.asDoubleList();
        QVERIFY(dl.size() == 3);
        QVERIFY(dl.at(0) == 2.5);
        QVERIFY(dl.at(1) == -0.125);
        QVERIFY(dl.at(2) == 13);
    }

    void testTagOperators()
    {
        DcmTagDS tag(DcmTagKey(0x1234, 0x5678));

        tag = 0.125;

        QVERIFY(tag.multiplicity() == 1);
        QVERIFY(tag() == 0.125);
        QVERIFY(tag[0] == 0.125);

        tag << 13.0;

        QVERIFY(tag.multiplicity() == 2);
        QVERIFY(tag[0] == 0.125);
        QVERIFY(tag[1] == 13.0);
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMTAGSTRING_H
