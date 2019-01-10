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

#include <QRegExp>
#include "DcmGlobal.h"

bool dcmIsValidUID(const QString &uid)
{
    QRegExp exp("^\\d*(\\.\\d*)*$");
    return exp.exactMatch(uid.trimmed());
}

bool dcmIsValidDateString(const QString &da)
{
    QRegExp exp("(\\d{4,4}(0\\d|1[0-2])([0-2]\\d|3[01]))?");
    return exp.exactMatch(da.trimmed());
}

QDate dcmStringToDate(const QString &str)
{
    return QDate::fromString(str, "yyyyMMdd");
}

QString dcmDateToString(const QDate &date)
{
    return date.toString("yyyyMMdd");
}

QTime dcmStringToTime(const QString &str)
{
    int period = str.indexOf(".");
    QTime time = QTime::fromString(str.left(6), "HHmmss");

    if (period < 0) {
        return time;
    }

    float frac = str.mid(period).toFloat();

    time.setHMS(time.hour(), time.minute(), time.second(), frac * 1000.0f);

    return time;
}

QString dcmTimeToString(const QTime &time)
{
    return time.toString("HHmmss.zzz");
}

QString dcmDateTimeToString(const QDateTime &dateTime)
{
    return dateTime.toString("yyyyMMddHHmmss.zzz");
}

QDateTime dcmStringToDateTime(const QString &str)
{
    int period = str.indexOf(".");
    QDateTime dateTime = QDateTime::fromString(str.left(14), "yyyyMMddHHmmss");

    if (period < 0) {
        return dateTime;
    }

    float frac = str.mid(period).toFloat();

    QTime time = dateTime.time();
    dateTime.setTime(QTime(time.hour(), time.minute(), time.second(), frac * 1000.0f));

    return dateTime;
}

bool dcmIsValidAgeString(const QString &as)
{
    QRegExp exp("^\\d{3}(D|W|M|Y)$");
    return exp.exactMatch(as.trimmed());
}
