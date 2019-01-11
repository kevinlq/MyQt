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
#include "DcmApplicationContext.h"

const DcmApplicationContext DcmApplicationContext::Invalid;
const DcmApplicationContext DcmApplicationContext::Default("1.2.840.10008.3.1.1.1");

DcmApplicationContext::DcmApplicationContext()
    : DcmPDUItem(DcmPDUType_ApplicationContext),
      m_uid()
{
}

DcmApplicationContext::DcmApplicationContext(const QString &uid)
    : DcmPDUItem(DcmPDUType_ApplicationContext),
      m_uid(uid)
{
    Q_ASSERT(dcmIsValidUID(m_uid));
}

DcmApplicationContext::DcmApplicationContext(const DcmApplicationContext &applicationContext)
    : DcmPDUItem(applicationContext),
      m_uid(applicationContext.m_uid)
{
}

DcmApplicationContext& DcmApplicationContext::operator =(const DcmApplicationContext &applicationContext)
{
    if (this != &applicationContext) {
        DcmPDUItem::operator =(applicationContext);
        m_uid = applicationContext.m_uid;
    }
    return *this;
}

DcmPDUItem* DcmApplicationContext::clone() const
{
    return new DcmApplicationContext(*this);
}

DcmApplicationContext::~DcmApplicationContext()
{
}

QString DcmApplicationContext::uid() const
{
    return m_uid;
}

bool DcmApplicationContext::operator ==(const DcmApplicationContext &applicationContext)
{
    return m_uid == applicationContext.m_uid;
}

bool DcmApplicationContext::operator !=(const DcmApplicationContext &applicationContext)
{
    return m_uid != applicationContext.m_uid;
}

DcmSize DcmApplicationContext::contentSize() const
{
    return m_uid.length();
}

bool DcmApplicationContext::isValid() const
{
    return !m_uid.isEmpty();
}

DcmStream& operator <<(DcmStream &stream, const DcmApplicationContext &pdu)
{
    char c[2] = {DcmPDUType_ApplicationContext, 0};
    stream.dataStream().writeRawData(c, 2);
    DcmUnsignedShort length = pdu.contentSize();
    stream.writePDUSize16(length);
    stream.dataStream().writeRawData(pdu.uid().toLocal8Bit(), length);
    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmApplicationContext &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_ApplicationContext && c[1] == 0) {
        DcmUnsignedShort length = stream.readPDUSize16();
        char *buffer = new char[length];
        stream.dataStream().readRawData(buffer, length);
        QString uid = QString::fromLocal8Bit(buffer, length);
        pdu = DcmApplicationContext(uid);
        delete[] buffer;
    } else {
        pdu = DcmApplicationContext::Invalid;
    }

    return stream;
}
