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

#include "DcmTagDS.h"

DcmTagDS::DcmTagDS()
    : DcmTagString(DcmTagKey(), DcmVr::DS)
{
}

DcmTagDS::DcmTagDS(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::DS)
{
}

DcmTagDS::DcmTagDS(const DcmTagDS &tag)
    : DcmTagString(tag)
{
}

DcmTagDS& DcmTagDS::operator =(const DcmTagDS &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagDS::clone() const
{
    return new DcmTagDS(*this);
}

DcmTagDS::~DcmTagDS()
{
}

void DcmTagDS::setValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Double) {
        str = QString::number(v.toDouble());
    } else if (v.type() == QVariant::Int) {
        str = QString::number(v.toInt());
    } else {
        str = v.toString();
    }

    setString(str);
}

void DcmTagDS::appendValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Double) {
        str = QString::number(v.toDouble());
    } else if (v.type() == QVariant::Int) {
        str = QString::number(v.toInt());
    } else {
        str = v.toString();
    }

    appendString(str);
}

DcmTagDS& DcmTagDS::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

double DcmTagDS::asDouble() const
{
    QString str = asString().left(16);
    int idx = asString().indexOf("\\");
    if (idx != -1) {
        str = str.left(idx);
    }

    return str.toDouble();
}

QList<double> DcmTagDS::asDoubleList() const
{
    QStringList sl = asStringList();
    QList<double> dl;

    foreach (QString s, sl) {
        dl.append(s.toDouble());
    }

    return dl;
}

void DcmTagDS::setDouble(double v)
{
    setString(QString::number(v));
}

void DcmTagDS::appendDouble(double v)
{
    appendString(QString::number(v));
}
