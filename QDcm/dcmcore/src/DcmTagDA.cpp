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

#include <QDebug>
#include "DcmGlobal.h"
#include "DcmTagDA.h"

DcmTagDA::DcmTagDA()
    : DcmTagString(DcmTagKey(), DcmVr::DA)
{
}

DcmTagDA::DcmTagDA(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::DA)
{
}

DcmTagDA::DcmTagDA(const DcmTagDA &tag)
    : DcmTagString(tag)
{
}

DcmTagDA& DcmTagDA::operator =(const DcmTagDA &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagDA::clone() const
{
    return new DcmTagDA(*this);
}

DcmTagDA::~DcmTagDA()
{
}

void DcmTagDA::setValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Date) {
        str = dcmDateToString(v.toDate());
    } else {
        str = v.toString().trimmed();
    }

    setString(str);
}

void DcmTagDA::appendValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Date) {
        str = dcmDateToString(v.toDate());
    } else {
        str = v.toString().trimmed();
    }

    appendString(str);
}

DcmTagDA& DcmTagDA::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

QDate DcmTagDA::asDate() const
{
    return dcmStringToDate(asString());
}

QList<QDate> DcmTagDA::asDatesList() const
{
    QStringList sl = asStringList();
    QList<QDate> dl;

    foreach(QString s, sl) {
        dl.append(dcmStringToDate(s));
    }

    return dl;
}

void DcmTagDA::setDate(const QDate &date)
{
    setString(dcmDateToString(date));
}

void DcmTagDA::appendDate(const QDate &date)
{
    appendString(dcmDateToString(date));
}
