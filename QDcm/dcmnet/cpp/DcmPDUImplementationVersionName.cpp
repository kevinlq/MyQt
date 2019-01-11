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

#include "DcmPDUImplementationVersionName.h"

DcmPDUImplementationVersionName::DcmPDUImplementationVersionName()
    : DcmPDUItem(DcmPDUType_ImplementationVersionName),
      m_name()
{
}

DcmPDUImplementationVersionName::DcmPDUImplementationVersionName(const QString &name)
    : DcmPDUItem(DcmPDUType_ImplementationVersionName),
      m_name(name)
{
}

DcmPDUImplementationVersionName::DcmPDUImplementationVersionName(const DcmPDUImplementationVersionName &pdu)
    : DcmPDUItem(pdu),
      m_name(pdu.m_name)
{
}

DcmPDUImplementationVersionName& DcmPDUImplementationVersionName::operator =(const DcmPDUImplementationVersionName &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_name = pdu.m_name;
    }
    return *this;
}

DcmPDUItem* DcmPDUImplementationVersionName::clone() const
{
    return new DcmPDUImplementationVersionName(*this);
}

DcmPDUImplementationVersionName::~DcmPDUImplementationVersionName()
{
}

QString DcmPDUImplementationVersionName::name() const
{
    return m_name;
}

DcmSize DcmPDUImplementationVersionName::contentSize() const
{
    return m_name.length();
}

bool DcmPDUImplementationVersionName::isValid() const
{
    return !m_name.isEmpty();
}

DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationVersionName &pdu)
{
    char c[2] = {DcmPDUType_ImplementationVersionName, 0};
    DcmUnsignedShort length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);

    stream.dataStream().writeRawData(pdu.m_name.toLocal8Bit(), length);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationVersionName &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_ImplementationVersionName && c[1] == 0) {
        DcmUnsignedShort length = stream.readPDUSize16();

        char *buffer = new char[length];
        stream.dataStream().readRawData(buffer, length);
        QString name = QString::fromLocal8Bit(buffer, length);
        delete[] buffer;

        pdu = DcmPDUImplementationVersionName(name);
    }

    return stream;
}

