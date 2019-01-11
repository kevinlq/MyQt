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

#include "DcmAcceptedPresentationContext.h"

const DcmAcceptedPresentationContext DcmAcceptedPresentationContext::Invalid;

DcmAcceptedPresentationContext::DcmAcceptedPresentationContext()
    : DcmPDUItem(DcmPDUType_AcceptedPresentationContext),
      m_id(0),
      m_reason(DcmAcceptedPresentationContext::Reason_NoReason),
      m_transferSyntax()
{
}

DcmAcceptedPresentationContext::DcmAcceptedPresentationContext(const DcmTransferSyntax &ts,
                                                               DcmAcceptedPresentationContext::Reason reason,
                                                               int id)
    : DcmPDUItem(DcmPDUType_AcceptedPresentationContext),
      m_id((DcmUnsignedShort)id),
      m_reason(reason),
      m_transferSyntax(ts)
{
    Q_ASSERT(id >= 0 && id < 256);
}

DcmAcceptedPresentationContext::DcmAcceptedPresentationContext(const DcmAcceptedPresentationContext &pc)
    : DcmPDUItem(pc),
      m_id(pc.m_id),
      m_reason(pc.m_reason),
      m_transferSyntax(pc.m_transferSyntax)
{
}

DcmAcceptedPresentationContext& DcmAcceptedPresentationContext::operator =(const DcmAcceptedPresentationContext &pc)
{
    if (this != &pc) {
        DcmPDUItem::operator =(pc);
        m_id = pc.m_id;
        m_reason = pc.m_reason;
        m_transferSyntax = pc.m_transferSyntax;
    }
    return *this;
}

DcmPDUItem* DcmAcceptedPresentationContext::clone() const
{
    return new DcmAcceptedPresentationContext(*this);
}

DcmAcceptedPresentationContext::~DcmAcceptedPresentationContext()
{
}

DcmTransferSyntax DcmAcceptedPresentationContext::transferSyntax() const
{
    return m_transferSyntax;
}

DcmAcceptedPresentationContext::Reason DcmAcceptedPresentationContext::reason() const
{
    return m_reason;
}

int DcmAcceptedPresentationContext::id() const
{
    return (int)m_id;
}

DcmSize DcmAcceptedPresentationContext::contentSize() const
{
    if (m_transferSyntax.isValid()) {
        return m_transferSyntax.size() + 4;
    }
    return 4;
}

bool DcmAcceptedPresentationContext::isValid() const
{
    return m_transferSyntax.isValid();
}

bool DcmAcceptedPresentationContext::isAccepted() const
{
    return m_reason == DcmAcceptedPresentationContext::Reason_Acceptance;
}

DcmStream& operator <<(DcmStream &stream, const DcmAcceptedPresentationContext &pdu)
{
    char c[2] = {DcmPDUType_AcceptedPresentationContext, 0};
    DcmUnsignedShort length = pdu.contentSize();

    char c2[4];
    c2[0] = (char)pdu.id();
    c2[1] = 0;
    c2[2] = (char)pdu.reason();
    c2[3] = 0;

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);
    stream.dataStream().writeRawData(c2, 4);

    // For invalid transfer syntax meaning it has not been accepted we
    // do not write the transfer syntax. The size already accounts for that.
    if (pdu.transferSyntax().isValid())
        stream << pdu.transferSyntax();

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAcceptedPresentationContext &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AcceptedPresentationContext && c[1] == 0) {
        DcmUnsignedShort length;
        DcmUnsignedShort readLength = 0;
        length = stream.readPDUSize16();
        DcmUnsignedByte id;
        stream >> id;
        stream.dataStream().skipRawData(1);
        DcmUnsignedByte reason;
        stream >> reason;
        stream.dataStream().skipRawData(1);

        readLength += 4;

        if (readLength >= length) {
            // If there is not transfer syntax, the abstract syntax has not been accepted.
            pdu = DcmAcceptedPresentationContext(DcmTransferSyntax::Invalid,
                                                 (DcmAcceptedPresentationContext::Reason)reason,
                                                 id);
        } else {
            DcmTransferSyntax ts;
            stream >> ts;

            readLength += ts.size();
            pdu = DcmAcceptedPresentationContext(ts,
                                                 (DcmAcceptedPresentationContext::Reason)reason,
                                                 id);
        }
    } else
        pdu = DcmAcceptedPresentationContext::Invalid;

    return stream;
}
