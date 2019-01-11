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

#include "DcmPresentationContext.h"

const DcmPresentationContext DcmPresentationContext::Invalid;

DcmPresentationContext::DcmPresentationContext()
    : DcmPDUItem(DcmPDUType_PresentationContext),
      m_id(),
      m_abstractSyntax(),
      m_transferSyntaxList()
{
}

DcmPresentationContext::DcmPresentationContext(const DcmAbstractSyntax &as, int id)
    : DcmPDUItem(DcmPDUType_PresentationContext),
      m_id((DcmUnsignedByte)id),
      m_abstractSyntax(as),
      m_transferSyntaxList()
{
    Q_ASSERT(id >= 0 && id < 256);
}

DcmPresentationContext::DcmPresentationContext(const DcmPresentationContext &pc)
    : DcmPDUItem(pc),
      m_id(pc.m_id),
      m_abstractSyntax(pc.m_abstractSyntax),
      m_transferSyntaxList(pc.m_transferSyntaxList)
{
}

DcmPresentationContext& DcmPresentationContext::operator =(const DcmPresentationContext &pc)
{
    if (this != &pc) {
        DcmPDUItem::operator =(pc);
        m_id = pc.m_id;
        m_abstractSyntax = pc.m_abstractSyntax;
        m_transferSyntaxList = pc.m_transferSyntaxList;
    }
    return *this;
}

DcmPDUItem* DcmPresentationContext::clone() const
{
    return new DcmPresentationContext(*this);
}

DcmPresentationContext::~DcmPresentationContext()
{
}

DcmAbstractSyntax DcmPresentationContext::abstractSyntax() const
{
    return m_abstractSyntax;
}

QList<DcmTransferSyntax> DcmPresentationContext::transferSyntaxes() const
{
    return m_transferSyntaxList;
}

void DcmPresentationContext::addTransferSyntax(const DcmTransferSyntax &ts)
{
    if (!ts.isValid()) {
        return;
    }
    if (!m_transferSyntaxList.contains(ts)) {
        m_transferSyntaxList.append(ts);
    }
}

int DcmPresentationContext::id() const
{
    return (int)m_id;
}

void DcmPresentationContext::setId(int id)
{
    Q_ASSERT(id >= 0 && id < 256);
    m_id = (DcmUnsignedByte)id;
}

DcmSize DcmPresentationContext::contentSize() const
{
    DcmSize s = 4;  // id 00 00 00
    s += m_abstractSyntax.size();
    foreach (DcmTransferSyntax ts, m_transferSyntaxList) {
        s += ts.size();
    }
    return s;
}

bool DcmPresentationContext::isValid() const
{
    return m_abstractSyntax.isValid() && m_transferSyntaxList.count() > 0;
}

DcmStream& operator <<(DcmStream &stream, const DcmPresentationContext &pdu)
{
    char c[2] = {DcmPDUType_PresentationContext, 0};
    DcmUnsignedShort length = pdu.contentSize();

    char c2[4] = {0, 0, 0, 0};
    c2[0] = pdu.m_id;

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);
    stream.dataStream().writeRawData(c2, 4);

    stream << pdu.m_abstractSyntax;
    foreach (DcmTransferSyntax ts, pdu.m_transferSyntaxList) {
        stream << ts;
    }

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmPresentationContext &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_PresentationContext && c[1] == 0) {
        DcmUnsignedShort length;
        DcmUnsignedShort readLength = 0;
        length = stream.readPDUSize16();
        DcmUnsignedByte id;
        stream >> id;
        stream.dataStream().skipRawData(3);
        readLength += 4;

        DcmAbstractSyntax abstractSyntax;

        stream >> abstractSyntax;
        if (!abstractSyntax.isValid()) {
            pdu = DcmPresentationContext::Invalid;
            return stream;
        }

        readLength += abstractSyntax.uid().length() + 4;
        pdu = DcmPresentationContext(abstractSyntax, id);

        // Read transfer syntaxes
        while (length > readLength) {
            DcmTransferSyntax ts;
            stream >> ts;

            if (!ts.isValid()) {
                pdu = DcmPresentationContext::Invalid;
                return stream;
            }

            readLength += ts.uid().length() + 4;
            pdu.addTransferSyntax(ts);
        }

        if (readLength > length) {
            pdu = DcmPresentationContext::Invalid;
            return stream;
        }
    } else {
        pdu = DcmPresentationContext::Invalid;
    }

    return stream;
}
