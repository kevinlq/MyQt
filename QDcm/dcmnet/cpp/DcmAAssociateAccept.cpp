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
#include "DcmAAssociateAccept.h"

DcmAAssociateAccept::DcmAAssociateAccept()
    : DcmPDUItem(DcmPDUType_AAssociateAc),
      m_protocolVersion(0x0100),
      m_calledAE(),
      m_callingAE(),
      m_applicationContext(DcmApplicationContext::Default),
      m_acceptedPesentationContextsList(),
      m_userInfoPDU()
{
}

DcmAAssociateAccept::DcmAAssociateAccept(const DcmAAssociateAccept &pdu)
    : DcmPDUItem(pdu),
      m_protocolVersion(pdu.m_protocolVersion),
      m_calledAE(pdu.m_calledAE),
      m_callingAE(pdu.m_callingAE),
      m_applicationContext(pdu.m_applicationContext),
      m_acceptedPesentationContextsList(pdu.m_acceptedPesentationContextsList),
      m_userInfoPDU(pdu.m_userInfoPDU)
{
}

DcmAAssociateAccept& DcmAAssociateAccept::operator =(const DcmAAssociateAccept &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_protocolVersion = pdu.m_protocolVersion;
        m_calledAE = pdu.m_calledAE;
        m_callingAE = pdu.m_callingAE;
        m_applicationContext = pdu.m_applicationContext;
        m_acceptedPesentationContextsList = pdu.m_acceptedPesentationContextsList;
        m_userInfoPDU = pdu.m_userInfoPDU;
    }
    return *this;
}

DcmPDUItem* DcmAAssociateAccept::clone() const
{
    return new DcmAAssociateAccept(*this);
}

DcmAAssociateAccept::~DcmAAssociateAccept()
{
}

DcmUnsignedShort DcmAAssociateAccept::protocolVersion() const
{
    return m_protocolVersion;
}

void DcmAAssociateAccept::setProtocolVersion(DcmUnsignedShort version)
{
    m_protocolVersion = version;
}

QString DcmAAssociateAccept::calledAE() const
{
    return m_calledAE;
}

void DcmAAssociateAccept::setCalledAE(const QString &ae)
{
    m_calledAE = ae;
}

QString DcmAAssociateAccept::callingAE() const
{
    return m_callingAE;
}

void DcmAAssociateAccept::setCallingAE(const QString &ae)
{
    m_callingAE = ae;
}

DcmApplicationContext DcmAAssociateAccept::applicationContext() const
{
    return m_applicationContext;
}

void DcmAAssociateAccept::setApplicationContext(const DcmApplicationContext &ac)
{
    m_applicationContext = ac;
}

int DcmAAssociateAccept::numberOfAcceptedPresentationContexts() const
{
    return m_acceptedPesentationContextsList.count();
}

DcmAcceptedPresentationContext* DcmAAssociateAccept::acceptedPresentationContextAt(int index) const
{
    return dynamic_cast<DcmAcceptedPresentationContext*>(m_acceptedPesentationContextsList.at(index));
}

void DcmAAssociateAccept::addAcceptedPresentationContext(const DcmAcceptedPresentationContext &apc)
{
    m_acceptedPesentationContextsList.append(apc);
}

void DcmAAssociateAccept::addAndRetainAcceptedPresentationContext(DcmAcceptedPresentationContext *apcPtr)
{
    m_acceptedPesentationContextsList.appendAndRetain(apcPtr);
}

DcmPDUUserInfo DcmAAssociateAccept::userInfoPDU() const
{
    return m_userInfoPDU;
}

void DcmAAssociateAccept::setUserInfoPDU(const DcmPDUUserInfo &pdu)
{
    m_userInfoPDU = pdu;
}

DcmSize DcmAAssociateAccept::size() const
{
    return 6 + contentSize();
}

DcmSize DcmAAssociateAccept::contentSize() const
{
    return 2        // Protocol version
            + 2     // 0x0000 reserver
            + 16    // Called AE
            + 16    // Calling AE
            + 32    // 0x00 reserved
            + m_applicationContext.size()
            + m_acceptedPesentationContextsList.size()
            + m_userInfoPDU.size();
}

bool DcmAAssociateAccept::isValid() const
{
    return (!m_calledAE.isEmpty())
            && (!m_callingAE.isEmpty())
            && m_applicationContext.isValid()
            && (m_acceptedPesentationContextsList.count() > 0)
            && m_userInfoPDU.isValid();
}

DcmStream& operator <<(DcmStream &stream, const DcmAAssociateAccept &pdu)
{
    char c[2] = {DcmPDUType_AAssociateAc, 0};
    DcmSize length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize32(length);

    char c2[32] = {'\0'};
    char c3[16] = {' '};

    stream << pdu.protocolVersion();
    stream.dataStream().writeRawData(c2, 2);

    stream.dataStream().writeRawData(pdu.m_calledAE.toLocal8Bit(), pdu.m_calledAE.length());
    if (pdu.m_calledAE.length() < 16)
        stream.dataStream().writeRawData(c3, 16 - pdu.m_calledAE.length());

    stream.dataStream().writeRawData(pdu.m_callingAE.toLocal8Bit(), pdu.m_callingAE.length());
    if (pdu.m_callingAE.length() < 16)
        stream.dataStream().writeRawData(c3, 16 - pdu.m_callingAE.length());

    stream.dataStream().writeRawData(c2, 32);

    stream << pdu.m_applicationContext;

    for (int i = 0; i < pdu.m_acceptedPesentationContextsList.count(); i++) {
        stream << *pdu.acceptedPresentationContextAt(i);
    }

    stream << pdu.m_userInfoPDU;

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAAssociateAccept &pdu)
{
    DcmNetStream netStream(stream);
    DcmAAssociateAccept acc;

    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AAssociateAc && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();

        DcmSize read = 0;

        DcmUnsignedShort protocolVersion;
        stream >> protocolVersion;
        acc.setProtocolVersion(protocolVersion);
        read += 2;

        stream.dataStream().skipRawData(2);
        read += 2;

        char ae[16];
        stream.dataStream().readRawData(ae, 16);
        read += 16;
        QString calledAE = QString::fromLocal8Bit(ae, 16).trimmed();
        stream.dataStream().readRawData(ae, 16);
        read += 16;
        QString callingAE = QString::fromLocal8Bit(ae, 16).trimmed();
        acc.setCalledAE(calledAE);
        acc.setCallingAE(callingAE);

        stream.dataStream().skipRawData(32);
        read += 32;

        while (read < length) {
            DcmPDUItem *item = netStream.readPDUItem();
            if (!item)
                break;
            read += item->size();

            if (item->type() == DcmPDUType_ApplicationContext) {
                DcmApplicationContext *context = dynamic_cast<DcmApplicationContext*>(item);
                Q_ASSERT(context);
                acc.setApplicationContext(*context);
                delete item;
            } else if (item->type() == DcmPDUType_AcceptedPresentationContext) {
                DcmAcceptedPresentationContext *context = dynamic_cast<DcmAcceptedPresentationContext*>(item);
                Q_ASSERT(context);
                acc.addAndRetainAcceptedPresentationContext(context);
            } else if (item->type() == DcmPDUType_UserInfo) {
                DcmPDUUserInfo *userInfo = dynamic_cast<DcmPDUUserInfo*>(item);
                Q_ASSERT(userInfo);
                acc.setUserInfoPDU(*userInfo);
                delete item;
            } else
                delete item;
        }

        pdu = acc;
    }

    return stream;
}
