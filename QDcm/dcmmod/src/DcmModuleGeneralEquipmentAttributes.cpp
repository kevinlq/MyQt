/* This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include "DcmGlobal.h"
#include "DcmTagDA.h"
#include "DcmTagTM.h"
#include "DcmModuleGeneralEquipmentAttributes.h"

DcmModuleGeneralEquipmentAttributes::DcmModuleGeneralEquipmentAttributes()
    : DcmModule("GeneralEquipmentAttributes")
{
    initializeTags();
}

DcmModuleGeneralEquipmentAttributes::DcmModuleGeneralEquipmentAttributes(const DcmModuleGeneralEquipmentAttributes &module)
    : DcmModule(module)
{
}

DcmModuleGeneralEquipmentAttributes& DcmModuleGeneralEquipmentAttributes::operator =(const DcmModuleGeneralEquipmentAttributes &module)
{
    if (this != &module) {
        DcmModule::operator =(module);
    }
    return *this;
}

DcmModule* DcmModuleGeneralEquipmentAttributes::clone() const
{
    return new DcmModuleGeneralEquipmentAttributes(*this);
}

QString DcmModuleGeneralEquipmentAttributes::manufacturer() const
{
    return tagValue("Manufacturer").toString();
}

void DcmModuleGeneralEquipmentAttributes::setManufacturer(const QString &value)
{
    setTagValue("Manufacturer", value);
}

QString DcmModuleGeneralEquipmentAttributes::institutionName() const
{
    return tagValue("InstitutionName").toString();
}

void DcmModuleGeneralEquipmentAttributes::setInstitutionName(const QString &value)
{
    setTagValue("InstitutionName", value);
}

QString DcmModuleGeneralEquipmentAttributes::institutionAddress() const
{
    return tagValue("InstitutionAddress").toString();
}

void DcmModuleGeneralEquipmentAttributes::setInstitutionAddress(const QString &value)
{
    setTagValue("InstitutionAddress", value);
}

QString DcmModuleGeneralEquipmentAttributes::stationName() const
{
    return tagValue("StationName").toString();
}

void DcmModuleGeneralEquipmentAttributes::setStationName(const QString &value)
{
    setTagValue("StationName", value);
}

QString DcmModuleGeneralEquipmentAttributes::institutionalDepartmentName() const
{
    return tagValue("InstitutionalDepartmentName").toString();
}

void DcmModuleGeneralEquipmentAttributes::setInstitutionalDepartmentName(const QString &value)
{
    setTagValue("InstitutionalDepartmentName", value);
}

QString DcmModuleGeneralEquipmentAttributes::manufacturerModelName() const
{
    return tagValue("ManufacturerModelName").toString();
}

void DcmModuleGeneralEquipmentAttributes::setManufacturerModelName(const QString &value)
{
    setTagValue("ManufacturerModelName", value);
}

QString DcmModuleGeneralEquipmentAttributes::deviceSerialNumber() const
{
    return tagValue("DeviceSerialNumber").toString();
}

void DcmModuleGeneralEquipmentAttributes::setDeviceSerialNumber(const QString &value)
{
    setTagValue("DeviceSerialNumber", value);
}

QString DcmModuleGeneralEquipmentAttributes::softwareVersions() const
{
    return tagValue("SoftwareVersions").toString();
}

void DcmModuleGeneralEquipmentAttributes::setSoftwareVersions(const QString &value)
{
    setTagValue("SoftwareVersions", value);
}

double DcmModuleGeneralEquipmentAttributes::spatialResolution() const
{
    return tagValue("SpatialResolution").toDouble();
}

void DcmModuleGeneralEquipmentAttributes::setSpatialResolution(double value)
{
    setTagValue("SpatialResolution", value);
}

QDate DcmModuleGeneralEquipmentAttributes::dateOfLastCalibration() const
{
    DcmTag *tagPtr = tag("DateOfLastCalibration");
    if (tagPtr) {
        DcmTagDA *tagDate = dynamic_cast<DcmTagDA*>(tagPtr);
        if (tagDate) {
            return tagDate->asDate();
        }
    }
    return QDate();
}

void DcmModuleGeneralEquipmentAttributes::setDateOfLastCalibration(const QDate &value)
{
    setTagValue("DateOfLastCalibration", value);
}

QTime DcmModuleGeneralEquipmentAttributes::timeOfLastCalibration() const
{
    DcmTag *tagPtr = tag("TimeOfLastCalibration");
    if (tagPtr) {
        DcmTagTM *tagTime = dynamic_cast<DcmTagTM*>(tagPtr);
        if (tagTime) {
            return tagTime->asTime();
        }
    }
    return QTime();
}

void DcmModuleGeneralEquipmentAttributes::setTimeOfLastCalibration(const QTime &value)
{
    setTagValue("TimeOfLastCalibration", value);
}

int DcmModuleGeneralEquipmentAttributes::pixelPaddingValue() const
{
    return tagValue("PixelPaddingValue").toInt();
}

void DcmModuleGeneralEquipmentAttributes::setPixelPaddingValue(int value)
{
    setTagValue("PixelPaddingValue", value);
}

void DcmModuleGeneralEquipmentAttributes::initializeTags()
{
    addSupportedTag("Manufacturer", DcmModule::TagType_2);
    addSupportedTag("InstitutionName", DcmModule::TagType_3);
    addSupportedTag("InstitutionAddress", DcmModule::TagType_3);
    addSupportedTag("StationName", DcmModule::TagType_3);
    addSupportedTag("InstitutionalDepartmentName", DcmModule::TagType_3);
    addSupportedTag("ManufacturerModelName", DcmModule::TagType_3);
    addSupportedTag("DeviceSerialNumber", DcmModule::TagType_3);
    addSupportedTag("SoftwareVersions", DcmModule::TagType_3);
    addSupportedTag("SpatialResolution", DcmModule::TagType_3);
    addSupportedTag("DateOfLastCalibration", DcmModule::TagType_3);
    addSupportedTag("TimeOfLastCalibration", DcmModule::TagType_3);
    addSupportedTag("PixelPaddingValue", DcmModule::TagType_3);
}
