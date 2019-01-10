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
#include "DcmModuleSOPCommon.h"

DcmModuleSOPCommon::DcmModuleSOPCommon()
    : DcmModule("SOPCommon")
{
    initializeTags();
}

DcmModuleSOPCommon::DcmModuleSOPCommon(const DcmModuleSOPCommon &module)
    : DcmModule(module)
{
}

DcmModuleSOPCommon& DcmModuleSOPCommon::operator =(const DcmModuleSOPCommon &module)
{
    if (this != &module) {
        DcmModule::operator =(module);
    }
    return *this;
}

DcmModule* DcmModuleSOPCommon::clone() const
{
    return new DcmModuleSOPCommon(*this);
}

QString DcmModuleSOPCommon::SOPClassUID() const
{
    return tagValue("SOPClassUID").toString();
}

void DcmModuleSOPCommon::setSOPClassUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("SOPClassUID", uid);
}

QString DcmModuleSOPCommon::SOPInstanceUID() const
{
    return tagValue("SOPInstanceUID").toString();
}

void DcmModuleSOPCommon::setSOPInstanceUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("SOPInstanceUID", uid);
}

QDate DcmModuleSOPCommon::instanceCreationDate() const
{
    DcmTag *tagPtr = tag("InstanceCreationDate");
    if (tagPtr) {
        DcmTagDA *tagDate = dynamic_cast<DcmTagDA*>(tagPtr);
        if (tagDate) {
            return tagDate->asDate();
        }
    }
    return QDate();
}

void DcmModuleSOPCommon::setInstanceCreationDate(const QDate &date)
{
    setTagValue("InstanceCreationDate", date);
}

QTime DcmModuleSOPCommon::instanceCreationTime() const
{
    DcmTag *tagPtr = tag("InstanceCreationTime");
    if (tagPtr) {
        DcmTagTM *tagTime = dynamic_cast<DcmTagTM*>(tagPtr);
        if (tagTime) {
            return tagTime->asTime();
        }
    }
    return QTime();
}

void DcmModuleSOPCommon::setInstanceCreationTime(const QTime &time)
{
    setTagValue("InstanceCreationTime", time);
}

QString DcmModuleSOPCommon::instanceCreatorUID() const
{
    return tagValue("InstanceCreatorUID").toString();
}

void DcmModuleSOPCommon::setInstanceCreatorUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("InstanceCreatorUID", uid);
}

void DcmModuleSOPCommon::initializeTags()
{
    addSupportedTag("SOPClassUID", DcmModule::TagType_1);
    addSupportedTag("SOPInstanceUID", DcmModule::TagType_1);
    addSupportedTag("SpecificCharacterSet", DcmModule::TagType_1C);
    addSupportedTag("InstanceCreationDate", DcmModule::TagType_3);
    addSupportedTag("InstanceCreationTime", DcmModule::TagType_3);
    addSupportedTag("InstanceCreatorUID", DcmModule::TagType_3);
    addSupportedTag("RelatedGeneralSOPClassUID", DcmModule::TagType_3);
    addSupportedTag("OriginalSpecializedSOPClassUID", DcmModule::TagType_3);
    addSupportedTag("CodingSchemeIdentificationSequence", DcmModule::TagType_3);
    addSupportedTag("TimezoneOffsetFromUTC", DcmModule::TagType_3);
    addSupportedTag("ContributingEquipmentSequence", DcmModule::TagType_3);
    addSupportedTag("InstanceNumber", DcmModule::TagType_3);
    addSupportedTag("SOPInstanceStatus", DcmModule::TagType_3);
    addSupportedTag("SOPAuthorizationDateTime", DcmModule::TagType_3);
    addSupportedTag("SOPAuthorizationComment", DcmModule::TagType_3);
    addSupportedTag("AuthorizationEquipmentCertificationNumber", DcmModule::TagType_3);
    addSupportedTag("EncryptedAttributesSequence", DcmModule::TagType_1C);
    addSupportedTag("OriginalAttributesSequence", DcmModule::TagType_3);
    addSupportedTag("HL7StructuredDocumentReferenceSequence", DcmModule::TagType_3);
}

