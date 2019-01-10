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

#ifndef DCMMODULESOPCOMMON_H
#define DCMMODULESOPCOMMON_H

#include "DcmModuleApi.h"
#include "DcmModule.h"

/*! SOP common module.
 * This module handles the following tags:
 * 0008, 0016   SOP Class UID               M
 * 0008, 0018   SOP Instance UID            M
 * 0008, 0012   Instance creation date      M
 * 0008, 0013   Instance creation time      M
 * 0008, 0014   Instance creator UID        O
 */
class DCM_MODULE_API DcmModuleSOPCommon: public DcmModule
{
public:

    /**
     * Construct the module with void tags.
     */
    DcmModuleSOPCommon();

    /**
     * Copy cinstructor.
     * \param module Module to be copied.
     */
    DcmModuleSOPCommon(const DcmModuleSOPCommon &module);

    /**
     * Assignment operator.
     * \param module Module to assign.
     * \return This module.
     */
    DcmModuleSOPCommon& operator =(const DcmModuleSOPCommon &module);

    /**
     * Clone this module.
     * \return Pointer to a cloned module.
     */
    DcmModule* clone() const;

    /**
     * Returns SOP Class UID (0008, 0016).
     * \return SOP Class UID.
     */
    QString SOPClassUID() const;

    /**
     * Assign SOP class UID (0008, 0016).
     * \param uid UID to be set.
     */
    void setSOPClassUID(const QString &uid);

    /**
     * Returns SOP instance UID (0008, 0018).
     * \return SOP instance UID.
     */
    QString SOPInstanceUID() const;

    /**
     * Assign SOP instance UID (0008, 0018).
     * \param uid UID to be set.
     */
    void setSOPInstanceUID(const QString &uid);

    /**
     * Returns instance creation date (0008, 0012).
     * \return Instance creation date.
     */
    QDate instanceCreationDate() const;

    /**
     * Assign instance creation date (0008, 0012).
     * \param date Date to be set.
     */
    void setInstanceCreationDate(const QDate &date);

    /**
     * Returns instance creation time (0008, 0013).
     * \return Instance creation time.
     */
    QTime instanceCreationTime() const;

    /**
     * Assign instance creation time (0008, 0013).
     * \param time Time to be set.
     */
    void setInstanceCreationTime(const QTime &time);

    /**
     * Returns instance creator UID (0008, 0014).
     * \return Instance creator UID.
     */
    QString instanceCreatorUID() const;

    /**
     * Assign instance creator UID (0008, 0014).
     * \param uid UID to be set.
     */
    void setInstanceCreatorUID(const QString &uid);

private:

    /**
     * Initialize tags lists.
     */
    void initializeTags();
};

#endif // DCMMODULESOPCOMMON_H
