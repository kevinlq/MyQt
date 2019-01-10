#ifndef TESTDCMIMAGE_H
#define TESTDCMIMAGE_H

#include <QDebug>
#include <QtTest/QtTest>
#include "DcmFile.h"
#include "DcmTagPixelData.h"
#include "DcmImage.h"

class TestDcmImage: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testImageFromDataset()
    {
        DcmDataset dataset;

        // Construct a bare minimum dataset for image fetch
        dataset.setTagValue("Rows", 512);
        dataset.setTagValue("Columns", 320);
        dataset.setTagValue("BitsAllocated", 16);
        dataset.setTagValue("BitsStored", 12);
        dataset.setTagValue("HighBit", 11);
        dataset.setTagValue("SamplesPerPixel", 1);
        dataset.setTagValue("PhotometricInterpretation", "MONOCHROME2");
        dataset.setTagValue("RescaleType", QString("HU"));
        dataset.setTagValue("RescaleIntercept", QVariant(-1200.0));
        dataset.setTagValue("RescaleSlope", QVariant(1.25));

        DcmTagPixelData tagPixelData(DcmTagPixelData::Format_Native, DcmVr::OW);
        QByteArray ba(512*320*2, 0);
        tagPixelData.setValue(ba);

        dataset.insert(tagPixelData);

        DcmImage image(dataset);

        QVERIFY(image.isValid());

        QCOMPARE(image.width(), 320);
        QCOMPARE(image.height(), 512);
        QCOMPARE(image.frames(), 1);
        QCOMPARE(image.bitsAllocated(), 16);
        QCOMPARE(image.bitsStored(), 12);
        QCOMPARE(image.highBit(), 11);
        QCOMPARE(image.samplesPerPixel(), 1);
        QCOMPARE(image.photometricInterpretation(), DcmPhotometricInterpretation::Monochrome2);
        DcmTagPixelData *tag =
                dynamic_cast<DcmTagPixelData*>(image.dataset().findTag(DcmTagKey::PixelData));
        QVERIFY(tag);
        QCOMPARE(tag, image.tagPixelData());
        QCOMPARE(tag->asByteArray().size(), 512*320*2);
        QCOMPARE(image.rescaleTypeString(), QString("HU"));
        QCOMPARE(image.rescaleIntercept(), -1200.0);
        QCOMPARE(image.rescaleSlope(), 1.25);

        // Test pixel data index calculation
        int x = 12;
        int y = 36;
        quint32 idx = (x + y * 320) * 2;
        QCOMPARE(idx, image.pixelByteArrayIndex(x, y));
    }

#if 0
    void testImageLoad()
    {
        QString path = "E:/DICOM/test/test.dcm";
        DcmFile dcmFile(path);
        QVERIFY(dcmFile.exists());

        DcmDataset dataset = dcmFile.read();
        if (dcmFile.isError()) {
            qDebug() << "ERROR:" << dcmFile.errorText();
        }

        QVERIFY(!dcmFile.isError());

        DcmImage image(dataset);

        delete dataset;

        qDebug() << "width:" << image.width();
        qDebug() << "height:" << image.height();
        qDebug() << "frames:" << image.frames();
        qDebug() << "bits allocated:" << image.bitsAllocated();
        qDebug() << "bits stored:" << image.bitsStored();
        qDebug() << "PI:" << image.photometricInterpretation().toString();

    }
#endif

    void cleanupTestCase()
    {}

};

#endif // TESTDCMIMAGE_H
