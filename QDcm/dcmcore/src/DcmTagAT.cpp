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

#include "DcmTagAT.h"

DcmTagAT::DcmTagAT()
    : DcmTag(DcmTagKey(), DcmVr::AT),
      m_values()
{
}

DcmTagAT::DcmTagAT(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::AT),
      m_values()
{
}

DcmTagAT::DcmTagAT(const DcmTagAT &tag)
    : DcmTag(tag),
      m_values(tag.m_values)
{
}

DcmTagAT& DcmTagAT::operator =(const DcmTagAT &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagAT::clone() const
{
    return new DcmTagAT(*this);
}

DcmTagAT::~DcmTagAT()
{
}

QVariant DcmTagAT::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0).hash());
    }

    return QVariant();
}

QVariantList DcmTagAT::values() const
{
    QVariantList res;

    foreach (DcmTagKey v, m_values) {
        res.append(QVariant(v.hash()));
    }

    return res;
}

void DcmTagAT::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append(DcmTagKey(v.toUInt()));
    }
}

void DcmTagAT::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append(DcmTagKey(v.toUInt()));
    }
}

DcmTagAT& DcmTagAT::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagAT::multiplicity() const
{
    return m_values.count();
}

DcmTagKey DcmTagAT::asDcmTagKey() const
{
    if (m_values.count() > 0) {
        return DcmTagKey(m_values.at(0));
    }

    return DcmTagKey();
}

QList<DcmTagKey> DcmTagAT::asDcmTagKeyList() const
{
    return m_values;
}

void DcmTagAT::setDcmTagKey(const DcmTagKey &v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagAT::appendDcmTagKey(const DcmTagKey &v)
{
    m_values.append(v);
}

DcmSize DcmTagAT::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 4 * multiplicity();
}
