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

#include "DcmNetStream.h"
#include "DcmPDUMaxLength.h"
#include "DcmPDUImplementationClassUID.h"
#include "DcmPDUImplementationVersionName.h"
#include "DcmPDUUserInfo.h"

DcmPDUUserInfo::DcmPDUUserInfo()
    : DcmPDUItem(DcmPDUType_UserInfo),
      m_itemsList()
{
}

DcmPDUUserInfo::DcmPDUUserInfo(const DcmPDUUserInfo &pdu)
    : DcmPDUItem(pdu),
      m_itemsList(pdu.m_itemsList)
{
}

DcmPDUUserInfo& DcmPDUUserInfo::operator =(const DcmPDUUserInfo &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_itemsList = pdu.m_itemsList;
    }
    return *this;
}

DcmPDUItem* DcmPDUUserInfo::clone() const
{
    return new DcmPDUUserInfo(*this);
}

DcmPDUUserInfo::~DcmPDUUserInfo()
{
}

int DcmPDUUserInfo::count() const
{
    return m_itemsList.count();
}

void DcmPDUUserInfo::clear()
{
    m_itemsList.clear();
}

DcmPDUItem* DcmPDUUserInfo::at(int index) const
{
    return m_itemsList.at(index);
}

void DcmPDUUserInfo::append(const DcmPDUItem &pdu)
{
    m_itemsList.append(pdu);
}

void DcmPDUUserInfo::appendAndRetain(DcmPDUItem *pduPtr)
{
    m_itemsList.appendAndRetain(pduPtr);
}

DcmSize DcmPDUUserInfo::contentSize() const
{
    return m_itemsList.size();
}

bool DcmPDUUserInfo::isValid() const
{
    return m_itemsList.count() > 0;
}

DcmSize DcmPDUUserInfo::pduMaxLength(DcmSize defaultLength) const
{
    DcmPDUItem *item = findPDUItem(DcmPDUType_PDUMaxLength);
    if (item) {
        DcmPDUMaxLength *pdu = dynamic_cast<DcmPDUMaxLength*>(item);
        if (pdu) {
            return pdu->length();
        }
    }
    return defaultLength;
}

QString DcmPDUUserInfo::implementationClassUID() const
{
    DcmPDUItem *item = findPDUItem(DcmPDUType_ImplementationClassUID);
    if (item) {
        DcmPDUImplementationClassUID *pdu = dynamic_cast<DcmPDUImplementationClassUID*>(item);
        if (pdu) {
            return pdu->uid();
        }
    }
    return QString();
}

QString DcmPDUUserInfo::implementationVersionName() const
{
    DcmPDUItem *item = findPDUItem(DcmPDUType_ImplementationVersionName);
    if (item) {
        DcmPDUImplementationVersionName *pdu = dynamic_cast<DcmPDUImplementationVersionName*>(item);
        if (pdu) {
            return pdu->name();
        }
    }
    return QString();
}

DcmPDUItem* DcmPDUUserInfo::findPDUItem(DcmPDUType type) const
{
    for (int i = 0; i < m_itemsList.count(); i++) {
        DcmPDUItem *item = m_itemsList.at(i);
        if (item->type() == type) {
            return item;
        }
    }
    return 0;
}

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDUUserInfo &pdu)
{
    DcmNetStream netStream(stream);
    char c[2] = {DcmPDUType_UserInfo, 0};
    DcmUnsignedShort length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);

    for (int i = 0; i < pdu.count(); i++) {
        netStream.writePDUItem(*pdu.at(i));
    }

    return stream;
}

DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDUUserInfo &pdu)
{
    DcmNetStream netStream(stream);
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_UserInfo && c[1] == 0) {
        DcmUnsignedShort length;
        DcmUnsignedShort readLength = 0;
        length = stream.readPDUSize16();

        pdu.clear();

        while (length > readLength) {
            DcmPDUItem *pduPtr = netStream.readPDUItem();
            if (!pduPtr) {
                break;
            }

            pdu.appendAndRetain(pduPtr);
            readLength += pduPtr->size();
        }
    }

    return stream;
}
