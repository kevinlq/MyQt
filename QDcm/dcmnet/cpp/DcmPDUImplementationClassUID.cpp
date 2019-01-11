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

#include "DcmGlobal.h"
#include "DcmPDUImplementationClassUID.h"

DcmPDUImplementationClassUID::DcmPDUImplementationClassUID()
    : DcmPDUItem(DcmPDUType_ImplementationClassUID),
      m_uid()
{
}

DcmPDUImplementationClassUID::DcmPDUImplementationClassUID(const QString &uid)
    : DcmPDUItem(DcmPDUType_ImplementationClassUID),
      m_uid(uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
}

DcmPDUImplementationClassUID::DcmPDUImplementationClassUID(const DcmPDUImplementationClassUID &pdu)
    : DcmPDUItem(pdu),
      m_uid(pdu.m_uid)
{
}

DcmPDUImplementationClassUID& DcmPDUImplementationClassUID::operator =(const DcmPDUImplementationClassUID &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_uid = pdu.m_uid;
    }
    return *this;
}

DcmPDUItem* DcmPDUImplementationClassUID::clone() const
{
    return new DcmPDUImplementationClassUID(*this);
}

DcmPDUImplementationClassUID::~DcmPDUImplementationClassUID()
{
}

QString DcmPDUImplementationClassUID::uid() const
{
    return m_uid;
}

DcmSize DcmPDUImplementationClassUID::contentSize() const
{
    return m_uid.length();
}

bool DcmPDUImplementationClassUID::isValid() const
{
    return !m_uid.isEmpty();
}

DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationClassUID &pdu)
{
    char c[2] = {DcmPDUType_ImplementationClassUID, 0};
    DcmUnsignedShort length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);

    stream.dataStream().writeRawData(pdu.m_uid.toLocal8Bit(), length);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationClassUID &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_ImplementationClassUID && c[1] == 0) {
        DcmUnsignedShort length = stream.readPDUSize16();

        char *buffer = new char[length];
        stream.dataStream().readRawData(buffer, length);
        QString uid = QString::fromLocal8Bit(buffer, length);
        delete[] buffer;

        pdu = DcmPDUImplementationClassUID(uid);
    }
    return stream;
}

