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
#include "DcmTagBinary.h"

DcmTagBinary::DcmTagBinary()
    : DcmTag(),
      m_byteArray()
{
}

DcmTagBinary::DcmTagBinary(const DcmTagKey &tagKey, const DcmVr &vr)
    : DcmTag(tagKey, vr),
      m_byteArray()
{
    if (!vr.isBinary() && vr != DcmVr::None) {
        // 'None' VR is accepted (e.g. pixel data items).
        qCritical() << "Binary-based tag created with non-binary value representation" << vr.toString();
        setVr(DcmVr::Invalid);
    }
}

DcmTagBinary::DcmTagBinary(const DcmTagBinary &tag)
    : DcmTag(tag),
      m_byteArray(tag.m_byteArray)
{
}

DcmTagBinary& DcmTagBinary::operator =(const DcmTagBinary &tag)
{
    if (this != &tag) {
        DcmTag::operator =(tag);
        m_byteArray = tag.m_byteArray;
    }
    return *this;
}

DcmTag* DcmTagBinary::clone() const
{
    return new DcmTagBinary(*this);
}

DcmTagBinary::~DcmTagBinary()
{
}

bool DcmTagBinary::isBinary() const
{
    return true;
}

QVariant DcmTagBinary::value() const
{
    return QVariant(m_byteArray);
}

QVariantList DcmTagBinary::values() const
{
    QVariantList res;
    res.append(QVariant(m_byteArray));
    return res;
}

void DcmTagBinary::setValue(const QVariant &v)
{
    if (v.isValid()) {
        m_byteArray = v.toByteArray();
    }
}

void DcmTagBinary::appendValue(const QVariant &v)
{
    if (v.isValid()) {
        m_byteArray.append(v.toByteArray());
    }
}

DcmTagBinary& DcmTagBinary::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

int DcmTagBinary::multiplicity() const
{
    return 1;
}

QByteArray DcmTagBinary::asByteArray() const
{
    return m_byteArray;
}

QByteArray& DcmTagBinary::data()
{
    return m_byteArray;
}

const char* DcmTagBinary::constData() const
{
    return m_byteArray.constData();
}

void DcmTagBinary::setByteArray(const QByteArray &byteArray)
{
    m_byteArray = byteArray;
}

DcmSize DcmTagBinary::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    Q_UNUSED(transferSyntax)
    return m_byteArray.size();
}
