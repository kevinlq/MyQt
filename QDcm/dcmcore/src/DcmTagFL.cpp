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

#include "DcmTagFL.h"

DcmTagFL::DcmTagFL()
    : DcmTag(DcmTagKey(), DcmVr::FL),
      m_values()
{
}

DcmTagFL::DcmTagFL(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::FL),
      m_values()
{
}

DcmTagFL::DcmTagFL(const DcmTagFL &tag)
    : DcmTag(tag),
      m_values(tag.m_values)
{
}

DcmTagFL& DcmTagFL::operator =(const DcmTagFL &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_values = tag.m_values;
    }
    return *this;
}

DcmTag* DcmTagFL::clone() const
{
    return new DcmTagFL(*this);
}

DcmTagFL::~DcmTagFL()
{
}

QVariant DcmTagFL::value() const
{
    if (m_values.count() > 0) {
        return QVariant(m_values.at(0));
    }

    return QVariant();
}

QVariantList DcmTagFL::values() const
{
    QVariantList res;

    foreach (DcmFloat v, m_values) {
        res.append(QVariant(v));
    }

    return res;
}

void DcmTagFL::setValue(const QVariant &v)
{
    m_values.clear();
    if (v.isValid()) {
        m_values.append(v.toFloat());
    }
}

void DcmTagFL::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_values.append(v.toFloat());
    }
}

DcmTagFL& DcmTagFL::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagFL::multiplicity() const
{
    return m_values.count();
}

DcmFloat DcmTagFL::asFloat() const
{
    if (m_values.count() > 0) {
        return m_values.at(0);
    }

    return 0.0f;
}

QList<DcmFloat> DcmTagFL::asFloatList() const
{
    return m_values;
}

void DcmTagFL::setFloat(DcmFloat v)
{
    m_values.clear();
    m_values.append(v);
}

void DcmTagFL::appendFloat(DcmFloat v)
{
    m_values.append(v);
}

DcmSize DcmTagFL::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)

    return 4 * multiplicity();
}
