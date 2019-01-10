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

#include "DcmTagIS.h"

DcmTagIS::DcmTagIS()
    : DcmTagString(DcmTagKey(), DcmVr::IS)
{
}

DcmTagIS::DcmTagIS(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::IS)
{
}

DcmTagIS::DcmTagIS(const DcmTagIS &tag)
    : DcmTagString(tag)
{
}

DcmTagIS& DcmTagIS::operator =(const DcmTagIS &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagIS::clone() const
{
    return new DcmTagIS(*this);
}

DcmTagIS::~DcmTagIS()
{
}

void DcmTagIS::setValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Int) {
        str = QString::number(v.toInt());
    } else {
        str = v.toString();
    }

    setString(str);
}

void DcmTagIS::appendValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Int) {
        str = QString::number(v.toInt());
    } else {
        str = v.toString();
    }

    appendString(str);
}

int DcmTagIS::asInt() const
{
    QString str = asString().left(12);
    int idx = asString().indexOf("\\");
    if (idx != -1) {
        str = str.left(idx);
    }

    return str.toInt();
}

QList<int> DcmTagIS::asIntList() const
{
    QStringList sl = asStringList();
    QList<int> il;

    foreach (QString s, sl) {
        il.append(s.toInt());
    }

    return il;
}

void DcmTagIS::setInt(int v)
{
    setString(QString::number(v));
}

void DcmTagIS::appendInt(int v)
{
    appendString(QString::number(v));
}
