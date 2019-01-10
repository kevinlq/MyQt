#ifndef TESTDCMIMAGETRANSFERFUNCTION_H
#define TESTDCMIMAGETRANSFERFUNCTION_H

#include <QDebug>
#include <QtTest/QtTest>
#include "DcmFile.h"
#include "DcmImage.h"
#include "DcmMonochromeImage.h"
#include "DcmImageTransferFunction.h"

class TestDcmImageTransferFunction : public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {
    }

    void testTransferFunction()
    {
        DcmImageTransferFunction tf;

        QCOMPARE(tf.numberOfReferencePoints(), 0);

        tf.addReferencePoint(0.0, QColor(0, 0, 0));
        tf.addReferencePoint(100.0, QColor(0, 255, 127));

        QCOMPARE(tf.numberOfReferencePoints(), 2);

        QColor c = tf.colorForPixelValue(-10.0);
        QCOMPARE(c.red(), 0);
        QCOMPARE(c.green(), 0);
        QCOMPARE(c. blue(), 0);

        c = tf.colorForPixelValue(0.0);
        QCOMPARE(c.red(), 0);
        QCOMPARE(c.green(), 0);
        QCOMPARE(c. blue(), 0);

        c = tf.colorForPixelValue(50.0);
        QCOMPARE(c.red(), 0);
        QVERIFY(c.green() > 126 && c.green() < 129);
        QVERIFY(c.blue() > 62 && c.blue() < 66);

        c = tf.colorForPixelValue(100.0);
        QCOMPARE(c.red(), 0);
        QCOMPARE(c.green(), 255);
        QCOMPARE(c. blue(), 127);

        c = tf.colorForPixelValue(1000.0);
        QCOMPARE(c.red(), 0);
        QCOMPARE(c.green(), 255);
        QCOMPARE(c. blue(), 127);
    }

#if 0
    // Example of converting monochrome DICOM image to a PNG.
    void testImageToQImage()
    {
        QString path = "/dicom/test.dcm";
        DcmFile dcmFile(path);
        QVERIFY(dcmFile.exists());

        DcmDataset *dataset = dcmFile.read();
        if (dcmFile.isError()) {
            qDebug() << "ERROR:" << dcmFile.errorText();
        }

        QVERIFY(dataset);
        QVERIFY(!dcmFile.isError());

        DcmImage image(dataset);

        delete dataset;

        if (image.photometricInterpretation().isGrayscale()) {
            DcmMonochromeImage monoImage(image.dataset());

            DcmImageTransferFunction tf;
            // Full-scale CT modality, assume HU units.
            tf.addReferencePoint(-1000.0, QColor(0, 0, 0));
            tf.addReferencePoint(3000.0, QColor(255, 255, 255));
            QImage qImage = monoImage.toQImage(tf);
            qImage.save("test.png");
        } else {
            qDebug() << "Unable to convert: not a grayscale image";
        }
    }
#endif

    void cleanupTestCase()
    {
    }
};

#endif // TESTDCMIMAGETRANSFERFUNCTION_H
