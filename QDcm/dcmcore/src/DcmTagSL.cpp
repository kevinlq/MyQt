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

#include "DcmTagSL.h"

DcmTagSL::DcmTagSL()
    : DcmTag(DcmTagKey(), DcmVr::SL),
      m_values()
{
}

DcmTagSL::DcmTagSL(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::SL),
      m_values()
{
}

DcmTagSL::DcmTagSL(const DcmTagSL &tag)
    : DcmTag(tag),
      m_values()
{
}

DcmTagSL& DcmTagSL::operator =(const DcmTagSL &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagSL::clone() const
{
    return new DcmTagSL(*this);
}

DcmTagSL::~DcmTagSL()
{
}

QVariant DcmTagSL::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0));
    }

    return QVariant();
}

QVariantList DcmTagSL::values() const
{
    QVariantList res;

    foreach (DcmSignedLong v, m_values) {
        res.append(QVariant(v));
    }

    return res;
}

void DcmTagSL::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append((DcmSignedLong)v.toInt());
    }
}

void DcmTagSL::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append((DcmSignedLong)v.toInt());
    }
}

DcmTagSL& DcmTagSL::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagSL::multiplicity() const
{
    return m_values.count();
}

DcmSignedLong DcmTagSL::asSignedLong() const
{
    DcmSignedLong res = 0;
    if (m_values.count() > 0) {
        res = m_values.at(0);
    }

    return res;
}

QList<DcmSignedLong> DcmTagSL::asSignedLongList() const
{
    return m_values;
}

void DcmTagSL::setSignedLong(DcmSignedLong v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagSL::appendSignedLong(DcmSignedLong v)
{
    m_values.append(v);
}

DcmSize DcmTagSL::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 4 * multiplicity();
}
