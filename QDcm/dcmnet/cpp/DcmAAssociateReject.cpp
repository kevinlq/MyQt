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

#include <QObject>
#include "DcmAAssociateReject.h"

DcmAAssociateReject::DcmAAssociateReject()
    : DcmPDUItem(DcmPDUType_AAssociateRj),
      m_result(DcmAssociationResultType_RejectPermanent),
      m_source(DcmAssociationSourceType_ServiceProvider),
      m_reason(DcmAssociationReasonType_NoReason)
{
}

DcmAAssociateReject::DcmAAssociateReject(DcmAssociationResultType result,
                                         DcmAssociationSourceType source,
                                         DcmAssociationReasonType reason)
    : DcmPDUItem(DcmPDUType_AAssociateRj),
      m_result(result),
      m_source(source),
      m_reason(reason)
{
}

DcmAAssociateReject::DcmAAssociateReject(const DcmAAssociateReject &pdu)
    : DcmPDUItem(pdu),
      m_result(pdu.m_result),
      m_source(pdu.m_source),
      m_reason(pdu.m_reason)
{
}

DcmAAssociateReject& DcmAAssociateReject::operator =(const DcmAAssociateReject &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_result = pdu.m_result;
        m_source = pdu.m_source;
        m_reason = pdu.m_reason;
    }
    return *this;
}

DcmPDUItem* DcmAAssociateReject::clone() const
{
    return new DcmAAssociateReject(*this);
}

DcmAAssociateReject::~DcmAAssociateReject()
{
}

DcmAssociationResultType DcmAAssociateReject::result() const
{
    return m_result;
}

void DcmAAssociateReject::setResult(DcmAssociationResultType result)
{
    m_result = result;
}

DcmAssociationSourceType DcmAAssociateReject::source() const
{
    return m_source;
}

void DcmAAssociateReject::setSource(DcmAssociationSourceType source)
{
    m_source = source;
}

DcmAssociationReasonType DcmAAssociateReject::reason() const
{
    return m_reason;
}

void DcmAAssociateReject::setReason(DcmAssociationReasonType reason)
{
    m_reason = reason;
}

QString DcmAAssociateReject::reasonAsString() const
{
    switch (m_reason) {
    case DcmAssociationReasonType_NoReason:
        return QObject::tr("No reason given");
    case DcmAssociationReasonType_ApplicationContextNotSupported:
        return QObject::tr("Application context is not supported");
    case DcmAssociationReasonType_CallingAENotRecognized:
        return QObject::tr("Calling application entity (AE) is not recognized");
    case DcmAssociationReasonType_CalledAENotRecognized:
        return QObject::tr("Called application entity (AE) is not recognized");
    default:
        return QObject::tr("Unknown reason");
    }
}

DcmSize DcmAAssociateReject::size() const
{
    return 6 + contentSize();
}

DcmSize DcmAAssociateReject::contentSize() const
{
    return 4;
}

bool DcmAAssociateReject::isValid() const
{
    return true;
}

DcmStream& operator <<(DcmStream &stream, const DcmAAssociateReject &pdu)
{
    char c[2] = {DcmPDUType_AAssociateRj, 0};
    DcmSize length =  pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize32(length);

    char c2[4];
    c2[0] = 0x00;
    c2[1] = (char)pdu.m_result;
    c2[2] = (char)pdu.m_source;
    c2[3] = (char)pdu.m_reason;

    stream.dataStream().writeRawData(c2, 4);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAAssociateReject &pdu)
{
    char c[2];

    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AAssociateRj && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();
        Q_ASSERT(length == 4);
        char c2[4];
        stream.dataStream().readRawData(c2, 4);

        pdu.setResult((DcmAssociationResultType)c2[1]);
        pdu.setSource((DcmAssociationSourceType)c2[2]);
        pdu.setReason((DcmAssociationReasonType)c2[3]);
    }

    return stream;
}
