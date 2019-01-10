#ifndef TESTDCMMODULES_H
#define TESTDCMMODULES_H

#include <QtTest/QtTest>
#include "DcmDataset.h"
#include "DcmModuleSOPCommon.h"
#include "DcmModulePatient.h"
#include "DcmModuleStudy.h"
#include "DcmModuleGeneralEquipmentAttributes.h"

class TestDcmModules: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testDcmModuleSOPCommon()
    {
        DcmModuleSOPCommon mod;

        QVERIFY(!mod.isValid());

        mod.setSOPClassUID("1.2.3.4.5");
        mod.setSOPInstanceUID("2.3.4.5.6");
        mod.setInstanceCreatorUID("3.4.5.6.7");
        mod.setInstanceCreationDate(QDate(2010, 03, 15));
        mod.setInstanceCreationTime(QTime(13, 45, 16, 325));

        QVERIFY(mod.isValid());

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("SOPClassUID"));
        QVERIFY(dataset.findTag("SOPInstanceUID"));
        QVERIFY(dataset.findTag("InstanceCreatorUID"));
        QVERIFY(dataset.findTag("InstanceCreationDate"));
        QVERIFY(dataset.findTag("InstanceCreationTime"));

        DcmModuleSOPCommon mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());
        QCOMPARE(mod2.SOPClassUID(), QString("1.2.3.4.5"));
        QCOMPARE(mod2.SOPInstanceUID(), QString("2.3.4.5.6"));
        QCOMPARE(mod2.instanceCreatorUID(), QString("3.4.5.6.7"));
        QCOMPARE(mod2.instanceCreationDate(), QDate(2010, 03, 15));
        QCOMPARE(mod2.instanceCreationTime(), QTime(13, 45, 16, 325));
    }

    void testDcmModulePatient()
    {
        DcmModulePatient mod;

        QVERIFY(!mod.isValid());

        mod.setPatientId("PAT1234");
        mod.setPatientName("Brown^John");
        // Missing tags: birth date and sex.
        QVERIFY(!mod.isValid());
        mod.completeVoidTags();
        QVERIFY(mod.isValid());

        mod.setPatientBirthDate(QDate(1976, 12, 4));
        mod.setPatientBirthTime(QTime(5, 55, 35, 135));
        mod.setPatientSex("M");

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("PatientName"));
        QVERIFY(dataset.findTag("PatientID"));
        QVERIFY(dataset.findTag("PatientBirthDate"));
        QVERIFY(dataset.findTag("PatientBirthTime"));
        QVERIFY(dataset.findTag("PatientSex"));

        DcmModulePatient mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());
        QCOMPARE(mod2.patientName(), QString("Brown^John"));
        QCOMPARE(mod2.patientId(), QString("PAT1234"));
        QCOMPARE(mod2.patientBirthDate(), QDate(1976, 12, 4));
        QCOMPARE(mod2.patientBirthTime(), QTime(5, 55, 35, 135));
        QCOMPARE(mod2.patientSex(), QString("M"));
    }

    void testDcmModuleStudy()
    {
        DcmModuleStudy mod;

        QVERIFY(!mod.isValid());

        mod.setStudyInstanceUID("1.2.3.4.5.6");
        mod.setStudyDate(QDate(2011, 3, 4));
        mod.setStudyTime(QTime(7, 15, 38, 17));
        QVERIFY(mod.isValid());
        mod.setStudyId("SID");
        mod.setReferringPhysicianName("Who^Doctor");
        mod.setStudyDescription("Study description.");

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("StudyInstanceUID"));
        QVERIFY(dataset.findTag("StudyDate"));
        QVERIFY(dataset.findTag("StudyTime"));
        QVERIFY(dataset.findTag("StudyID"));
        QVERIFY(dataset.findTag("ReferringPhysicianName"));
        QVERIFY(dataset.findTag("StudyDescription"));

        DcmModuleStudy mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());
        QCOMPARE(mod2.studyInstanceUID(), QString("1.2.3.4.5.6"));
        QCOMPARE(mod2.studyDate(), QDate(2011, 3, 4));
        QCOMPARE(mod2.studyTime(), QTime(7, 15, 38, 17));
        QCOMPARE(mod2.studyId(), QString("SID"));
        QCOMPARE(mod2.referringPhysicianName(), QString("Who^Doctor"));
        QCOMPARE(mod2.studyDescription(), QString("Study description."));
    }

    void testDcmModuleEquipmentAttributes()
    {
        DcmModuleGeneralEquipmentAttributes mod;

        QVERIFY(!mod.isValid());
        mod.completeVoidTags();
        QVERIFY(mod.isValid());

        mod.setManufacturer("QDCM");
        mod.setInstitutionName("Hospital");
        mod.setInstitutionAddress("1, Street, City");
        mod.setStationName("Station A");
        mod.setInstitutionalDepartmentName("Radiology");
        mod.setManufacturerModelName("Model 1");
        mod.setDeviceSerialNumber("Device-0123");
        mod.setSoftwareVersions("QDCM-1.0");
        mod.setSpatialResolution(0.25);
        mod.setDateOfLastCalibration(QDate(2010, 3, 4));
        mod.setTimeOfLastCalibration(QTime(12, 20, 37, 6));
        mod.setPixelPaddingValue(3);

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("Manufacturer"));
        QVERIFY(dataset.findTag("InstitutionName"));
        QVERIFY(dataset.findTag("InstitutionAddress"));
        QVERIFY(dataset.findTag("StationName"));
        QVERIFY(dataset.findTag("InstitutionalDepartmentName"));
        QVERIFY(dataset.findTag("ManufacturerModelName"));
        QVERIFY(dataset.findTag("DeviceSerialNumber"));
        QVERIFY(dataset.findTag("SoftwareVersions"));
        QVERIFY(dataset.findTag("SpatialResolution"));
        QVERIFY(dataset.findTag("DateOfLastCalibration"));
        QVERIFY(dataset.findTag("TimeOfLastCalibration"));
        QVERIFY(dataset.findTag("PixelPaddingValue"));

        DcmModuleGeneralEquipmentAttributes mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());

        QCOMPARE(mod2.manufacturer(), QString("QDCM"));
        QCOMPARE(mod2.institutionName(), QString("Hospital"));
        QCOMPARE(mod2.institutionAddress(), QString("1, Street, City"));
        QCOMPARE(mod2.stationName(), QString("Station A"));
        QCOMPARE(mod2.institutionalDepartmentName(), QString("Radiology"));
        QCOMPARE(mod2.manufacturerModelName(), QString("Model 1"));
        QCOMPARE(mod2.deviceSerialNumber(), QString("Device-0123"));
        QCOMPARE(mod2.softwareVersions(), QString("QDCM-1.0"));
        QCOMPARE(mod2.spatialResolution(), 0.25);
        QCOMPARE(mod2.dateOfLastCalibration(), QDate(2010, 3, 4));
        QCOMPARE(mod2.timeOfLastCalibration(), QTime(12, 20, 37, 6));
        QCOMPARE(mod2.pixelPaddingValue(), 3);
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMMODULES_H
