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

#include "DcmTagSS.h"

DcmTagSS::DcmTagSS()
    : DcmTag(DcmTagKey(), DcmVr::SS),
      m_values()
{
}

DcmTagSS::DcmTagSS(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::SS),
      m_values()
{
}

DcmTagSS::DcmTagSS(const DcmTagSS &tag)
    : DcmTag(tag),
      m_values(tag.m_values)
{
}

DcmTagSS& DcmTagSS::operator =(const DcmTagSS &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagSS::clone() const
{
    return new DcmTagSS(*this);
}

DcmTagSS::~DcmTagSS()
{
}

QVariant DcmTagSS::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0));
    }

    return QVariant();
}

QVariantList DcmTagSS::values() const
{
    QVariantList res;

    foreach (DcmSignedShort v, m_values) {
        res.append(QVariant(v));
    }

    return res;
}

void DcmTagSS::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append((DcmSignedShort)v.toInt());
    }
}

void DcmTagSS::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append((DcmSignedShort)v.toInt());
    }
}

DcmTagSS& DcmTagSS::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagSS::multiplicity() const
{
    return m_values.count();
}

DcmSignedShort DcmTagSS::asSignedShort() const
{
    DcmSignedShort res = 0;
    if (m_values.count() > 0) {
        res = m_values.at(0);
    }

    return res;
}

QList<DcmSignedShort> DcmTagSS::asSignedShortList() const
{
    return m_values;
}

void DcmTagSS::setSignedShort(DcmSignedShort v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagSS::appendSignedShort(DcmSignedShort v)
{
    m_values.append(v);
}

DcmSize DcmTagSS::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 2 * multiplicity();
}
