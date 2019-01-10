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

#include "DcmTagUL.h"

DcmTagUL::DcmTagUL()
    : DcmTag(DcmTagKey(), DcmVr::UL),
      m_values()
{
}

DcmTagUL::DcmTagUL(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::UL),
      m_values()
{
}

DcmTagUL::DcmTagUL(const DcmTagUL &tag)
    : DcmTag(tag),
      m_values(tag.m_values)
{
}

DcmTagUL& DcmTagUL::operator =(const DcmTagUL &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagUL::clone() const
{
    return new DcmTagUL(*this);
}

DcmTagUL::~DcmTagUL()
{
}

QVariant DcmTagUL::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0));
    }

    return QVariant();
}

QVariantList DcmTagUL::values() const
{
    QVariantList res;

    foreach (DcmUnsignedLong v, m_values) {
        res.append(QVariant(v));
    }

    return res;
}

void DcmTagUL::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append((DcmUnsignedLong)v.toUInt());
    }
}

void DcmTagUL::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append((DcmUnsignedLong)v.toUInt());
    }
}

DcmTagUL& DcmTagUL::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagUL::multiplicity() const
{
    return m_values.count();
}

DcmUnsignedLong DcmTagUL::asUnsignedLong() const
{
    DcmUnsignedLong res = 0;
    if (m_values.count() > 0) {
        res = m_values.at(0);
    }

    return res;
}

QList<DcmUnsignedLong> DcmTagUL::asUnsignedLongList() const
{
    return m_values;
}

void DcmTagUL::setUnsignedLong(DcmUnsignedLong v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagUL::appendUnsignedLong(DcmUnsignedLong v)
{
    m_values.append(v);
}

DcmSize DcmTagUL::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 4 * multiplicity();
}
