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
#include "DcmModuleStudy.h"

DcmModuleStudy::DcmModuleStudy()
    : DcmModule("Study")
{
    initializeTags();
}

DcmModuleStudy::DcmModuleStudy(const DcmModuleStudy &module)
    : DcmModule(module)
{
}

DcmModuleStudy& DcmModuleStudy::operator =(const DcmModuleStudy &module)
{
    if (this != &module) {
        DcmModuleStudy::operator =(module);
    }
    return *this;
}

DcmModule* DcmModuleStudy::clone() const
{
    return new DcmModuleStudy(*this);
}

QString DcmModuleStudy::studyInstanceUID() const
{
    return tagValue("StudyInstanceUID").toString();
}

void DcmModuleStudy::setStudyInstanceUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("StudyInstanceUID", uid);
}

QDate DcmModuleStudy::studyDate() const
{
    DcmTag *tagPtr = tag("StudyDate");
    if (tagPtr) {
        DcmTagDA *tagDate = dynamic_cast<DcmTagDA*>(tagPtr);
        if (tagDate) {
            return tagDate->asDate();
        }
    }
    return QDate();
}

void DcmModuleStudy::setStudyDate(const QDate &date)
{
    setTagValue("StudyDate", date);
}

QTime DcmModuleStudy::studyTime() const
{
    DcmTag *tagPtr = tag("StudyTime");
    if (tagPtr) {
        DcmTagTM *tagTime = dynamic_cast<DcmTagTM*>(tagPtr);
        if (tagTime) {
            return tagTime->asTime();
        }
    }
    return QTime();
}

void DcmModuleStudy::setStudyTime(const QTime &time)
{
    setTagValue("StudyTime", time);
}

QString DcmModuleStudy::referringPhysicianName() const
{
    return tagValue("ReferringPhysicianName").toString();
}

void DcmModuleStudy::setReferringPhysicianName(const QString &name)
{
    setTagValue("ReferringPhysicianName", name);
}

QString DcmModuleStudy::studyId() const
{
    return tagValue("StudyID").toString();
}

void DcmModuleStudy::setStudyId(const QString &id)
{
    setTagValue("StudyID", id);
}

QString DcmModuleStudy::studyDescription() const
{
    return tagValue("StudyDescription").toString();
}

void DcmModuleStudy::setStudyDescription(const QString &desc)
{
    setTagValue("StudyDescription", desc);
}

void DcmModuleStudy::initializeTags()
{
    addSupportedTag("StudyInstanceUID", DcmModule::TagType_1);
    addSupportedTag("StudyDate", DcmModule::TagType_1);
    addSupportedTag("StudyTime", DcmModule::TagType_1);
    addSupportedTag("ReferringPhysicianName", DcmModule::TagType_3);
    addSupportedTag("StudyID", DcmModule::TagType_3);
    addSupportedTag("StudyDescription", DcmModule::TagType_3);
}
