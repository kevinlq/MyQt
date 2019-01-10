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

#include "DcmTagDA.h"
#include "DcmTagTM.h"
#include "DcmModulePatient.h"

DcmModulePatient::DcmModulePatient()
    : DcmModule("Patient")
{
    initializeTags();
}

DcmModulePatient::DcmModulePatient(const DcmModulePatient &module)
    : DcmModule(module)
{
}

DcmModulePatient& DcmModulePatient::operator =(const DcmModulePatient &module)
{
    if (this != &module) {
        DcmModule::operator =(module);
    }
    return *this;
}

DcmModule* DcmModulePatient::clone() const
{
    return new DcmModulePatient(*this);
}

QString DcmModulePatient::patientName() const
{
    return tagValue("PatientName").toString();
}

void DcmModulePatient::setPatientName(const QString &name)
{
    setTagValue("PatientName", name);
}

QString DcmModulePatient::patientId() const
{
    return tagValue("PatientID").toString();
}

void DcmModulePatient::setPatientId(const QString &id)
{
    setTagValue("PatientID", id);
}

QDate DcmModulePatient::patientBirthDate() const
{
    DcmTag *tagPtr = tag("PatientBirthDate");
    if (tagPtr) {
        DcmTagDA *tagDate = dynamic_cast<DcmTagDA*>(tagPtr);
        if (tagDate) {
            return tagDate->asDate();
        }
    }
    return QDate();
}

void DcmModulePatient::setPatientBirthDate(const QDate &date)
{
    setTagValue("PatientBirthDate", date);
}

QTime DcmModulePatient::patientBirthTime() const
{
    DcmTag *tagPtr = tag("PatientBirthTime");
    if (tagPtr) {
        DcmTagTM *tagTime = dynamic_cast<DcmTagTM*>(tagPtr);
        if (tagTime) {
            return tagTime->asTime();
        }
    }
    return QTime();
}

void DcmModulePatient::setPatientBirthTime(const QTime &time)
{
    setTagValue("PatientBirthTime", time);
}

QString DcmModulePatient::patientSex() const
{
    return tagValue("PatientSex").toString();
}

void DcmModulePatient::setPatientSex(const QString &s)
{
    setTagValue("PatientSex", s);
}

void DcmModulePatient::initializeTags()
{
    addSupportedTag("PatientName", DcmModule::TagType_2);
    addSupportedTag("PatientID", DcmModule::TagType_2);
    addSupportedTag("PatientBirthDate", DcmModule::TagType_2);
    addSupportedTag("PatientSex", DcmModule::TagType_2);
    addSupportedTag("ReferencedPatientSequence", DcmModule::TagType_3);
    addSupportedTag("PatientBirthTime", DcmModule::TagType_3);
    addSupportedTag("OtherPatientIDs", DcmModule::TagType_3);
    addSupportedTag("OtherPatientIDsSequence", DcmModule::TagType_3);
    addSupportedTag("OtherPatientNames", DcmModule::TagType_3);
    addSupportedTag("EthnicGroup", DcmModule::TagType_3);
    addSupportedTag("PatientComments", DcmModule::TagType_3);
    addSupportedTag("PatientSpeciesDescription", DcmModule::TagType_1C);
    addSupportedTag("PatientSpeciesCodeSequence", DcmModule::TagType_1C);
    addSupportedTag("PatientBreedDescription", DcmModule::TagType_2C);
    addSupportedTag("PatientBreedCodeSequence", DcmModule::TagType_2C);
    addSupportedTag("BreedRegistrationSequence", DcmModule::TagType_2C);
    addSupportedTag("ResponsiblePerson", DcmModule::TagType_2C);
    addSupportedTag("ResponsiblePersonRole", DcmModule::TagType_1C);
    addSupportedTag("ResponsibleOrganization", DcmModule::TagType_2C);
    addSupportedTag("PatientIdentityRemoved", DcmModule::TagType_3);   // 'YES' or 'NO'
    addSupportedTag("DeidentificationMethod", DcmModule::TagType_1C);
    addSupportedTag("DeidentificationMethodCodeSequence", DcmModule::TagType_1C);
}
