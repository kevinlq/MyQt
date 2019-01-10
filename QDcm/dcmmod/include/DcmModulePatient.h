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

#ifndef DCMMODULEPATIENT_H
#define DCMMODULEPATIENT_H

#include "DcmModuleApi.h"
#include "DcmModule.h"

/*! DICOM Patient module.
 * This module handles the following tags:
 * 0010, 0010       Patient name            M
 * 0010, 0020       Patient ID              M
 * 0010, 0030       Patient birth date      O
 * 0010, 0032       Patient birth time      O
 * 0010, 0040       Patient sex             O
 */
class DCM_MODULE_API DcmModulePatient: public DcmModule
{
public:

    /**
     * Construct patient module with void tags.
     */
    DcmModulePatient();

    /**
     * Copy constructor.
     * \param module Module to be copied.
     */
    DcmModulePatient(const DcmModulePatient &module);

    /**
     * Assignment operator.
     * \param module Module to be assigned.
     * \return This module.
     */
    DcmModulePatient& operator =(const DcmModulePatient &module);

    /**
     * Clone this module.
     * \return Pointer to the module clone.
     */
    DcmModule* clone() const;

    /**
     * Returns patient name (0010, 0010).
     * \return Patient name.
     */
    QString patientName() const;

    /**
     * Assign patient name (0010, 0010).
     * \param name Name to be set.
     */
    void setPatientName(const QString &name);

    /**
     * Returns patient ID (0010, 0020).
     * \return Patient ID.
     */
    QString patientId() const;

    /**
     * Assign patient ID (0010, 0020).
     * \param id Patient ID to be set.
     */
    void setPatientId(const QString &id);

    /**
     * Returns patient birth date (0010, 0030).
     * \return Patient birth date.
     */
    QDate patientBirthDate() const;

    /**
     * Assign patient birth date (0010, 0030).
     * \return date Birth date to be set.
     */
    void setPatientBirthDate(const QDate &date);

    /**
     * Reutns patient birth time (0010, 0032).
     * \return Patient birth time.
     */
    QTime patientBirthTime() const;

    /**
     * Assign petient birth time (0010, 0032).
     * \param time Birth time to be set.
     */
    void setPatientBirthTime(const QTime &time);

    /**
     * Returns patient sex (0010, 0040).
     * \return Patient sex.
     */
    QString patientSex() const;

    /**
     * Assign patient sex (0010, 0040).
     * \param s Patient sex to be set.
     */
    void setPatientSex(const QString &s);

private:

    /**
     * Initialize module tags list.
     */
    void initializeTags();
};

#endif // DCMMODULEPATIENT_H
