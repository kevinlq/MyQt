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

#ifndef DCMMODULESTUDY_H
#define DCMMODULESTUDY_H

#include "DcmModuleApi.h"
#include "DcmModule.h"

/*! DICOM Study module.
 * This module handles the following tags:
 * 0020, 000d       Study Instance UID          M
 * 0008, 0020       Study date                  M
 * 0008, 0030       Study time                  M
 * 0008, 0090       Referring physician name    O
 * 0020, 0010       Study ID                    O
 * 0008, 1030       Study description           O
 */
class DCM_MODULE_API DcmModuleStudy: public DcmModule
{
public:

    /**
     * Construct study module with void tags.
     */
    DcmModuleStudy();

    /**
     * Copy constructor.
     * \param module Module to be copied.
     */
    DcmModuleStudy(const DcmModuleStudy &module);

    /**
     * Assignment operator.
     * \param module Module to be assigned.
     * \return This module.
     */
    DcmModuleStudy& operator =(const DcmModuleStudy &module);

    /**
     * Clone this module.
     * \return Pointer to the module clone.
     */
    DcmModule* clone() const;

    /**
     * Returns study instance UID.
     * \return Study instance UID.
     */
    QString studyInstanceUID() const;

    /**
     * Assign study instance UID.
     * \param uid UID to be assigned.
     */
    void setStudyInstanceUID(const QString &uid);

    /**
     * Returns study date.
     * \return Study date.
     */
    QDate studyDate() const;

    /**
     * Assign study date.
     * \param date Date to be set.
     */
    void setStudyDate(const QDate &date);

    /**
     * Returns study time.
     * \return Study time.
     */
    QTime studyTime() const;

    /**
     * Assign study time.
     * \param time Time to be set.
     */
    void setStudyTime(const QTime &time);

    /**
     * Returns study physician name.
     * \return Physician name.
     */
    QString referringPhysicianName() const;

    /**
     * Assign study physician name.
     * \param name Name to be set.
     */
    void setReferringPhysicianName(const QString &name);

    /**
     * Returns study ID.
     * \return Study ID.
     */
    QString studyId() const;

    /**
     * Assign study ID.
     * \param id Study ID to be set.
     */
    void setStudyId(const QString &id);

    /**
     * Returns study description.
     * \return Study description.
     */
    QString studyDescription() const;

    /**
     * Assign study description.
     * \param desc Description to be set.
     */
    void setStudyDescription(const QString &desc);


private:

    /**
     * Initialize tags list.
     */
    void initializeTags();
};

#endif // DCMMODULESTUDY_H
