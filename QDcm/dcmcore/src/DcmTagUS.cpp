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

#include "DcmTagUS.h"

DcmTagUS::DcmTagUS()
    : DcmTag(DcmTagKey(), DcmVr::US),
      m_values()
{
}

DcmTagUS::DcmTagUS(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::US),
      m_values()
{
}

DcmTagUS::DcmTagUS(const DcmTagUS &tag)
    : DcmTag(tag),
      m_values(tag.m_values)
{
}

DcmTagUS& DcmTagUS::operator =(const DcmTagUS &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagUS::clone() const
{
    return new DcmTagUS(*this);
}

DcmTagUS::~DcmTagUS()
{
}

QVariant DcmTagUS::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0));
    }

    return QVariant();
}

QVariantList DcmTagUS::values() const
{
    QVariantList res;

    foreach (DcmUnsignedShort v, m_values) {
        res.append(QVariant(v));
    }

    return res;
}

void DcmTagUS::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append((DcmUnsignedShort)v.toUInt());
    }
}

void DcmTagUS::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append((DcmUnsignedShort)v.toUInt());
    }
}

DcmTagUS& DcmTagUS::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagUS::multiplicity() const
{
    return m_values.count();
}

DcmUnsignedShort DcmTagUS::asUnsignedShort() const
{
    DcmUnsignedShort res = 0;
    if (m_values.count() > 0) {
        res = m_values.at(0);
    }

    return res;
}

QList<DcmUnsignedShort> DcmTagUS::asUnsignedShortList() const
{
    return m_values;
}

void DcmTagUS::setUnsignedShort(DcmUnsignedShort v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagUS::appendUnsignedShort(DcmUnsignedShort v)
{
    m_values.append(v);
}

DcmSize DcmTagUS::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 2 * multiplicity();
}
