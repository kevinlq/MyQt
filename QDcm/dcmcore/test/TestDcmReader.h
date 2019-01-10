#ifndef TESTDCMREADER_H
#define TESTDCMREADER_H

#include <QDebug>
#include <QtTest/QtTest>
#include "DcmFile.h"
#include "DcmReader.h"
#include "DcmWriter.h"
#include "DcmStream.h"
#include "DcmTagPixelData.h"

class TestDcmReader: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testWriteAndRead()
    {
        DcmDataset dataset;

        dataset.setTagValue("MediaStorageSOPClassUID", "1.2.840.10008.5.1.4.1.1.1");
        dataset.setTagValue("MediaStorageSOPInstanceUID", "1.2.3.4.5.6.7");
        dataset.setTagValue("StudyInstanceUID", "1.2.3.4.5.6.7.1");
        dataset.setTagValue("SeriesInstanceUID", "1.2.3.4.5.6.7.1.1");
        dataset.setTagValue("SOPClassUID", "1.2.840.10008.5.1.4.1.1.1");
        dataset.setTagValue("SOPInstanceUID", "1.2.3.4.5.6.7");
        dataset.setTagValue("PatientId", "DF47K5");
        dataset.setTagValue("PatientName", "Brown^John");
        dataset.setTagValue("PatientSex", "M");
        dataset.setTagValue("PatientBirthDate", QDate(1975, 3, 15));

        QByteArray rawData;

        DcmStream wStream(&rawData, QIODevice::WriteOnly, DcmTransferSyntax::ExplicitLittleEndian);
        DcmWriter writer(&wStream);
        writer.writeDataset(dataset);

        QVERIFY(rawData.size() > 0);

        DcmStream rStream(&rawData, QIODevice::ReadOnly, DcmTransferSyntax::ExplicitLittleEndian);
        DcmReader reader(&rStream);

        DcmDataset ds = reader.readDataset();

        QVERIFY(!reader.isError());

        QCOMPARE(ds["MediaStorageSOPClassUID"].toString(), QString("1.2.840.10008.5.1.4.1.1.1"));
        QCOMPARE(ds["MediaStorageSOPInstanceUID"].toString(), QString("1.2.3.4.5.6.7"));
        QCOMPARE(ds["StudyInstanceUID"].toString(), QString("1.2.3.4.5.6.7.1"));
        QCOMPARE(ds["SeriesInstanceUID"].toString(), QString("1.2.3.4.5.6.7.1.1"));
        QCOMPARE(ds["SOPClassUID"].toString(), QString("1.2.840.10008.5.1.4.1.1.1"));
        QCOMPARE(ds["SOPInstanceUID"].toString(), QString("1.2.3.4.5.6.7"));
        QCOMPARE(ds["PatientId"].toString(), QString("DF47K5"));
        QCOMPARE(ds["PatientName"].toString(), QString("Brown^John"));
        QCOMPARE(ds["PatientSex"].toString(), QString("M"));
        QCOMPARE(ds["PatientBirthDate"].toString(), QString("19750315"));
    }

    void testTagDS()
    {
        QByteArray rawData;
        DcmStream wStream(&rawData, QIODevice::WriteOnly, DcmTransferSyntax::ImplicitLittleEndian);
        DcmWriter writer(&wStream);

        DcmTag *pTag = DcmTag::create(DcmTagKey(0x300b, 0x1018));
        pTag->setValue(3);
        QVERIFY(pTag);
        writer.writeTag(pTag);

        QVERIFY(rawData.size() == 10);

        delete pTag;
    }

#if 0
    void testBigEndian()
    {
        QString path = "E:/DICOM/BAD_DICOM/big_endian.dcm";
        DcmFile dcmFile(path);
        QVERIFY(dcmFile.exists());

        DcmDataset dataset = dcmFile.read();
        if (dcmFile.isError()) {
            qDebug() << "ERROR:" << dcmFile.errorText();
        } else {
            qDebug() << "ImageType" << dataset.findTag("ImageType")->value().toString();
            qDebug() << "Rows" << dataset.findTag("Rows")->value().toInt();
            qDebug() << "Columns" << dataset.findTag("Columns")->value().toInt();
        }
    }
#endif

#if 0
    void testReadWriteFile()
    {
        QString path = "E:/DICOM/BAD_DICOM/rtplan.dcm";
        DcmFile dcmFile(path);
        QVERIFY(dcmFile.exists());

        DcmDataset dataset = dcmFile.read();
        if (dcmFile.isError()) {
            qDebug() << "ERROR:" << dcmFile.errorText();
        } else {
            qDebug() << "CharSet:" << dataset.tagValue(DcmTagKey::SpecificCharacterSet).toString();

            DcmFile dcmOutputFile("output.dcm");
            dcmOutputFile.write(dataset, DcmTransferSyntax::ExplicitLittleEndian);
        }
    }
#endif

#if 0
    void testReadFile()
    {
        QString filePath = "E:/DICOM/test/compressed.dcm";

        DcmFile dcmFile(filePath);
        QVERIFY(dcmFile.exists());

        DcmDataset dataset = dcmFile.read();
        if (dcmFile.isError()) {
            qDebug() << "ERROR: " << dcmFile.errorText();
            return;
        }

        QVERIFY(!dcmFile.isError());

        // Fetch some tag
        qDebug() << "Patient name:" << dataset->tagValue("patientName");
        DcmTag *tagPatientName = dataset->findTag(DcmTagKey(0x0010, 0x0010));
        if (tagPatientName) {
            qDebug() << "PatientName: " << tagPatientName->value().toString();
        } else {
            qDebug() << "ERROR: Unable to fetch patient name tag";
        }

        DcmTag *tag = dataset->findTag(DcmTagKey::PixelData);
        if (tag) {
            DcmTagPixelData *tagPixelData = dynamic_cast<DcmTagPixelData*>(tag);
            if (tagPixelData) {
                if (tagPixelData->format() == DcmTagPixelData::Format_Native) {
                    QByteArray rawData = tagPixelData->asByteArray();
                    QFile file("pixeldata.raw");
                    if (file.open(QFile::WriteOnly)) {
                        file.write(rawData);
                        file.close();
                    }
                } else {
                    // Compressed stuff
                    int i = 0;
                    foreach(DcmTag *tag, tagPixelData->items().list()) {
                        DcmTagPixelDataItem *item = dynamic_cast<DcmTagPixelDataItem*>(tag);
                        QString filename = QString("enc_%1.raw").arg(i);
                        i++;
                        QByteArray ba = item->asByteArray();
                        QFile file(filename);
                        if (file.open(QFile::WriteOnly)) {
                            file.write(ba);
                            file.close();
                        }
                    }
                }
            }

            /*
            DcmFile dcmFile("output.dcm");
            dcmFile.write(dataset, DcmTransferSyntax::ImplicitLittleEndian);
            */

        }
    }
#endif

    void cleanupTestCase()
    {}
};

#endif // TESTDCMREADER_H
