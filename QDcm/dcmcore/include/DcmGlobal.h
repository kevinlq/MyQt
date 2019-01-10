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

#ifndef DCMGLOBAL_H
#define DCMGLOBAL_H

#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include "DcmCoreApi.h"

/**
 * Tells whether the UID is a valid one.
 * The valid UID is composed of numbers seperated by point '.' symbol.
 * \param uid UID to be verified.
 * \return true if UID is valid.
 */
bool DCM_CORE_API dcmIsValidUID(const QString &uid);

/**
 * Tells whether the date (DA) string is a valid one.
 * The valid date string has the format YYYYMMDD.
 * \param da Date string.
 * \return true if date string is valid.
 */
bool DCM_CORE_API dcmIsValidDateString(const QString &da);

/**
 * Converts string into date.
 * The string should represent a date in 'YYYYMMDD' format.
 * \param str String to be converted.
 * \return Date.
 */
QDate DCM_CORE_API dcmStringToDate(const QString &str);

/**
 * Convert date value into DICOM string.
 * The result string has format 'YYYYMMDD'.
 * \param date Date to be converted.
 * \return String representation of the date.
 */
QString DCM_CORE_API dcmDateToString(const QDate &date);

/**
 * Convert string into time.
 * The string should encode a time in format 'HHMMSS.ZZZ'.
 * \param str String to be converted.
 * \return Time.
 */
QTime DCM_CORE_API dcmStringToTime(const QString &str);

/**
 * Convert time into DICOM string.
 * The result string has format 'HHMMSS.ZZZ'.
 * \param time Time to be converted.
 * \return String representation of the time.
 */
QString DCM_CORE_API dcmTimeToString(const QTime &time);

/**
 * Convert string into date/time value.
 * The string should have format 'YYYYMMDDHHMMSS.ZZZ'.
 * \param str String to be converted.
 * \return Date/time value.
*/
QDateTime DCM_CORE_API dcmStringToDateTime(const QString &str);

/**
 * Convert date/time value into string.
 * The string format is 'YYYYMMDDHHMMSS.ZZZ'.
 * \param dateTime Date/time to be converted.
 * \return String representation of the date/time.
 */
QString DCM_CORE_API dcmDateTimeToString(const QDateTime &dateTime);

/**
 * Tells whether the age string (AS) value is a valid one.
 * The age string takes a 3-digits number followed by D, W, M, or Y symbol.
 * \param as Age string to be tested.
 * \return true if age string is valid.
 */
bool DCM_CORE_API dcmIsValidAgeString(const QString &as);

#endif // DCMGLOBAL_H
