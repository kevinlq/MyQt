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

#include "DcmStream.h"

DcmStream::DcmStream(const DcmTransferSyntax &transferSyntax)
    : m_dataStream()
{
    setTransferSyntax(transferSyntax);
}

DcmStream::DcmStream(QIODevice *ioDevice, const DcmTransferSyntax &transferSyntax)
    : m_dataStream(ioDevice)
{
    Q_ASSERT(ioDevice);
    setTransferSyntax(transferSyntax);
}

DcmStream::DcmStream(QByteArray *byteArray, QIODevice::OpenMode openMode, const DcmTransferSyntax &transferSyntax)
    : m_dataStream(byteArray, openMode)
{
    Q_ASSERT(byteArray);
    setTransferSyntax(transferSyntax);
}

DcmStream::DcmStream(const QByteArray &byteArray, const DcmTransferSyntax &transferSyntax)
    : m_dataStream(byteArray)
{
    setTransferSyntax(transferSyntax);
}

DcmTransferSyntax DcmStream::transferSyntax() const
{
    return m_transferSyntax;
}

void DcmStream::setTransferSyntax(const DcmTransferSyntax &transferSyntax)
{
    m_transferSyntax = transferSyntax;
    if (m_transferSyntax.endianess() == DcmEndianess_LittleEndian) {
        m_dataStream.setByteOrder(QDataStream::LittleEndian);
    } else {
        m_dataStream.setByteOrder(QDataStream::BigEndian);
    }
}

QDataStream& DcmStream::dataStream()
{
    return m_dataStream;
}

bool DcmStream::atEnd() const
{
    return m_dataStream.atEnd();
}

DcmStream& DcmStream::operator <<(DcmSignedByte value)
{
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmSignedByte &value)
{
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmUnsignedByte value)
{
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmUnsignedByte &value)
{
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmSignedShort value)
{
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmSignedShort &value)
{
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmUnsignedShort value)
{
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmUnsignedShort &value)
{
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmSignedLong value)
{
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmSignedLong &value)
{
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmUnsignedLong value)
{
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmUnsignedLong &value)
{
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmFloat value)
{
    m_dataStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmFloat &value)
{
    m_dataStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(DcmDouble value)
{
    m_dataStream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    m_dataStream << value;
    return *this;
}

DcmStream& DcmStream::operator >>(DcmDouble &value)
{
    m_dataStream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    m_dataStream >> value;
    return *this;
}

DcmStream& DcmStream::operator <<(const DcmTagKey &tagKey)
{
    m_dataStream << tagKey.group() << tagKey.element();
    return *this;
}

DcmStream& DcmStream::operator >>(DcmTagKey &tagKey)
{
    DcmUnsignedShort group;
    DcmUnsignedShort element;
    m_dataStream >> group >> element;
    tagKey.setGroup(group);
    tagKey.setElement(element);
    return *this;
}

DcmStream& DcmStream::operator <<(const DcmVr &vr)
{
    if (vr != DcmVr::None) {
        if (vr == DcmVr::Invalid) {
            // Encode invalid VR as unknown
            m_dataStream.writeRawData(DcmVr::UN.signature(), 2);
        } else {
            m_dataStream.writeRawData(vr.signature(), 2);
        }
    }
    return *this;
}

DcmStream& DcmStream::operator >>(DcmVr &vr)
{
    char signature[2];
    m_dataStream.readRawData(signature, 2);
    vr = DcmVr::bySignatrure(signature);

    return *this;
}

DcmStream& DcmStream::operator <<(const DcmTransferSyntax &ts)
{
    char c[2] = {DcmPDUType_TransferSyntax, 0};
    DcmUnsignedShort length = ts.contentSize();

    m_dataStream.writeRawData(c, 2);
    writePDUSize16(length);
    m_dataStream.writeRawData(ts.uid().toLatin1(), length);

    return *this;
}

DcmStream& DcmStream::operator >>(DcmTransferSyntax &ts)
{
    char c[2];
    m_dataStream.readRawData(c, 2);
    if (c[0] == DcmPDUType_TransferSyntax && c[1] == 0) {
        DcmUnsignedShort length = readPDUSize16();
        char *buffer = new char[length];
        m_dataStream.readRawData(buffer, length);
        QString uid = QString::fromLatin1(buffer, length);
        delete[] buffer;

        ts = DcmTransferSyntax::fromUid(uid);
        if (!ts.isValid()) {
            ts = DcmTransferSyntax(uid);
        }
    } else {
        ts = DcmTransferSyntax::Invalid;
    }

    return *this;
}

void DcmStream::writePDUSize32(DcmSize s)
{
    unsigned char c[4];
    c[0] = (s >> 24);
    c[1] = (s >> 16);
    c[2] = (s >> 8);
    c[3] = s & 0xFF;
    m_dataStream.writeRawData((char*)c, 4);
}

DcmSize DcmStream::readPDUSize32()
{
    unsigned char c[4];
    m_dataStream.readRawData((char*)c, 4);
    DcmSize s = ((DcmSize)c[0]) << 24;
    s |= ((DcmSize)c[1]) << 16;
    s |= ((DcmSize)c[2]) << 8;
    s |= ((DcmSize)c[3]);

    return s;
}

void DcmStream::writePDUSize16(DcmUnsignedShort s)
{
    unsigned char c[2];
    c[0] = (s >> 8);
    c[1] = (s & 0x00FF);
    m_dataStream.writeRawData((char*)c, 2);

}

DcmUnsignedShort DcmStream::readPDUSize16()
{
    char c[2];
    m_dataStream.readRawData(c, 2);
    DcmUnsignedShort s = (((DcmUnsignedShort)c[0]) << 8) | (DcmUnsignedShort)c[1];
    return s;
}
