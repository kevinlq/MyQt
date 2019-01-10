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

#include "DcmTagFD.h"

DcmTagFD::DcmTagFD()
    : DcmTag(DcmTagKey(), DcmVr::FD),
      m_values()
{
}

DcmTagFD::DcmTagFD(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::FD),
      m_values()
{
}

DcmTagFD::DcmTagFD(const DcmTagFD &tag)
    : DcmTag(tag),
      m_values(tag.m_values)
{
}

DcmTagFD& DcmTagFD::operator =(const DcmTagFD &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagFD::clone() const
{
    return new DcmTagFD(*this);
}

DcmTagFD::~DcmTagFD()
{
}

QVariant DcmTagFD::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0));
    }

    return QVariant();
}

QVariantList DcmTagFD::values() const
{
    QVariantList res;

    foreach (DcmDouble v, m_values) {
        res.append(QVariant(v));
    }

    return res;
}

void DcmTagFD::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append(v.toDouble());
    }
}

void DcmTagFD::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append(v.toDouble());
    }
}

DcmTagFD& DcmTagFD::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagFD::multiplicity() const
{
    return m_values.count();
}

DcmDouble DcmTagFD::asDouble() const
{
    if (m_values.count() > 0) {
        return m_values.at(0);
    }

    return 0.0;
}

QList<DcmDouble> DcmTagFD::asDoubleList() const
{
    return m_values;
}

void DcmTagFD::setDouble(DcmDouble v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagFD::appendDouble(DcmDouble v)
{
    m_values.append(v);
}

DcmSize DcmTagFD::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 8 * multiplicity();
}
