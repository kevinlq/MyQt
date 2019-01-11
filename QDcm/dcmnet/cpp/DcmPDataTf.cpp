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

#include "DcmPDataTf.h"

DcmPDataTf::DcmPDataTf()
    : DcmPDUItem(DcmPDUType_PData),
      m_pdvItemsList()
{
}

DcmPDataTf::DcmPDataTf(const DcmPDataTf &pdu)
    : DcmPDUItem(pdu),
      m_pdvItemsList()
{
    foreach (DcmPDVItem *pdv, pdu.m_pdvItemsList) {
        m_pdvItemsList.append(new DcmPDVItem(*pdv));
    }
}

DcmPDataTf& DcmPDataTf::operator =(const DcmPDataTf &pdu)
{
    if (this != &pdu) {
        clear();
        foreach (DcmPDVItem *pdv, pdu.m_pdvItemsList) {
            m_pdvItemsList.append(new DcmPDVItem(*pdv));
        }
    }
    return *this;
}

DcmPDUItem* DcmPDataTf::clone() const
{
    return new DcmPDataTf(*this);
}

DcmPDataTf::~DcmPDataTf()
{
    clear();
}

int DcmPDataTf::count() const
{
    return m_pdvItemsList.count();
}

DcmPDVItem* DcmPDataTf::at(int i) const
{
    if (i < 0 || i >= m_pdvItemsList.count()) {
        return 0;
    }
    return m_pdvItemsList.at(i);
}

void DcmPDataTf::addPDV(const DcmPDVItem &pdv)
{
    m_pdvItemsList.append(new DcmPDVItem(pdv));
}

void DcmPDataTf::addAndRetainPDV(DcmPDVItem *pdvPtr)
{
    Q_ASSERT(pdvPtr);
    if (pdvPtr) {
        m_pdvItemsList.append(pdvPtr);
    }
}

void DcmPDataTf::clear()
{
    foreach (DcmPDVItem *pdv, m_pdvItemsList) {
        delete pdv;
    }
    m_pdvItemsList.clear();
}

DcmSize DcmPDataTf::size() const
{
    return 6 + contentSize();
}

DcmSize DcmPDataTf::contentSize() const
{
    DcmSize s = 0;
    foreach (DcmPDVItem *pdv, m_pdvItemsList) {
        s += 4  // item length
                + 1 // presentation context id
                + 1 // PDV control header
                + pdv->dataSize();

    }
    return s;
}

bool DcmPDataTf::isValid() const
{
    return count() > 0;
}

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDataTf &pdu)
{
    char c[2] = {DcmPDUType_PData, 0};
    stream.dataStream().writeRawData(c, 2);

    DcmSize length = pdu.contentSize();
    stream.writePDUSize32(length);

    for (int i = 0; i < pdu.count(); i++) {
        DcmPDVItem *item = pdu.at(i);
        length = item->dataSize() + 2;
        c[0] = (char)item->presentationContextId();
        c[1] = 0x00;
        if (item->isCommand())
            c[1] |= 0x01;
        if (item->isTerminating())
            c[1] |= 0x02;
        stream.writePDUSize32(length);
        stream.dataStream().writeRawData(c, 2);
        stream.dataStream().writeRawData(item->constData(), item->dataSize());
    }

    return stream;
}

DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDataTf &pdu)
{
    char c[2];

    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_PData && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();

        pdu.clear();

        DcmSize done = 0;
        while (done < length) {
            // Read PDVs
            DcmSize itemLength;
            DcmUnsignedByte contextId;
            DcmUnsignedByte controlHeader;
            itemLength = stream.readPDUSize32();
            done +=4;
            stream >> contextId;
            done++;
            stream >> controlHeader;
            done++;
            char *rawData = new char[itemLength-2];
            stream.dataStream().readRawData(rawData, itemLength-2);
            done += itemLength - 2;

            DcmPDVItem *pdvItem = new DcmPDVItem(contextId, controlHeader & 0x01, controlHeader & 0x02);
            pdvItem->byteArray().append(rawData, itemLength-2);
            pdu.addAndRetainPDV(pdvItem);

            delete[] rawData;
        }
    }

    return stream;
}
