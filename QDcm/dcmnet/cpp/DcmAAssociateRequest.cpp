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

#include <QDebug>
#include "DcmNetStream.h"
#include "DcmAAssociateRequest.h"

DcmAAssociateRequest::DcmAAssociateRequest()
    : DcmPDUItem(DcmPDUType_AAssociateRq),
      m_protocolVersion(0x0100),
      m_calledAE(),
      m_callingAE(),
      m_applicationContext(DcmApplicationContext::Default),
      m_presentationContextList(),
      m_userInfoPDU()
{
}

DcmAAssociateRequest::DcmAAssociateRequest(const DcmAAssociateRequest &pdu)
    : DcmPDUItem(pdu),
      m_protocolVersion(pdu.m_protocolVersion),
      m_calledAE(pdu.m_calledAE),
      m_callingAE(pdu.m_callingAE),
      m_applicationContext(pdu.m_applicationContext),
      m_presentationContextList(pdu.m_presentationContextList),
      m_userInfoPDU(pdu.m_userInfoPDU)
{
}

DcmAAssociateRequest& DcmAAssociateRequest::operator =(const DcmAAssociateRequest &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_protocolVersion = pdu.m_protocolVersion;
        m_calledAE = pdu.m_calledAE;
        m_callingAE = pdu.m_callingAE;
        m_applicationContext = pdu.m_applicationContext;
        m_presentationContextList = pdu.m_presentationContextList;
        m_userInfoPDU = pdu.m_userInfoPDU;
    }
    return *this;
}

DcmPDUItem* DcmAAssociateRequest::clone() const
{
    return new DcmAAssociateRequest(*this);
}

DcmAAssociateRequest::~DcmAAssociateRequest()
{
}

QString DcmAAssociateRequest::calledAE() const
{
    return m_calledAE;
}

void DcmAAssociateRequest::setCalledAE(const QString &ae)
{
    m_calledAE = ae.left(16);
}

QString DcmAAssociateRequest::callingAE() const
{
    return m_callingAE;
}

void DcmAAssociateRequest::setCallingAE(const QString &ae)
{
    m_callingAE = ae.left(16);
}

DcmApplicationContext DcmAAssociateRequest::applicationContext() const
{
    return m_applicationContext;
}

void DcmAAssociateRequest::setApplicationContext(const DcmApplicationContext &ac)
{
    m_applicationContext = ac;
}

int DcmAAssociateRequest::numberOfPresentationContexts() const
{
    return m_presentationContextList.count();
}

DcmPresentationContext* DcmAAssociateRequest::presentationContextAt(int index) const
{
    return dynamic_cast<DcmPresentationContext*>(m_presentationContextList.at(index));
}

void DcmAAssociateRequest::addPresentationContext(const DcmPresentationContext &pc)
{
    m_presentationContextList.append(pc);
}

void DcmAAssociateRequest::addAndRetainPresentationContext(DcmPresentationContext *pcPtr)
{
    m_presentationContextList.appendAndRetain(pcPtr);
}

DcmPDUUserInfo DcmAAssociateRequest::userInfoPDU() const
{
    return m_userInfoPDU;
}

void DcmAAssociateRequest::setUserInfoPDU(const DcmPDUUserInfo &pdu)
{
    m_userInfoPDU = pdu;
}

DcmUnsignedShort DcmAAssociateRequest::protocolVersion() const
{
    return m_protocolVersion;
}

void DcmAAssociateRequest::setProtocolVersion(DcmUnsignedShort version)
{
    m_protocolVersion = version;
}

DcmSize DcmAAssociateRequest::size() const
{
    return contentSize() + 6;
}

DcmSize DcmAAssociateRequest::contentSize() const
{
    return 2        // protocol version
            + 2     // 0x0000 reserved
            + 16    // Called AE
            + 16    // Calling AE
            + 32    // 0x00 reserver
            + m_applicationContext.size()
            + m_presentationContextList.size()
            + m_userInfoPDU.size();
}

bool DcmAAssociateRequest::isValid() const
{
    return (!m_calledAE.isEmpty())
            && (!m_callingAE.isEmpty())
            && m_applicationContext.isValid()
            && (m_presentationContextList.count() > 0)
            && m_userInfoPDU.isValid();
}

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAssociateRequest &pdu)
{
    char c[2] = {DcmPDUType_AAssociateRq, 0};
    DcmSize length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize32(length);

    char c2[32] = {'\0'};
    char c3[16] = {' '};

    memset(c3, ' ', 16);

    stream << pdu.m_protocolVersion;
    stream.dataStream().writeRawData(c2, 2);

    stream.dataStream().writeRawData(pdu.m_calledAE.toLocal8Bit(), pdu.m_calledAE.length());
    if (pdu.m_calledAE.length() < 16)
        stream.dataStream().writeRawData(c3, 16 - pdu.m_calledAE.length());

    stream.dataStream().writeRawData(pdu.m_callingAE.toLocal8Bit(), pdu.m_callingAE.length());
    if (pdu.m_callingAE.length() < 16)
        stream.dataStream().writeRawData(c3, 16 - pdu.m_callingAE.length());

    stream.dataStream().writeRawData(c2, 32);

    stream << pdu.m_applicationContext;

    for (int i = 0; i < pdu.m_presentationContextList.count(); i++) {
        DcmPresentationContext *pcPtr = dynamic_cast<DcmPresentationContext*>(pdu.m_presentationContextList.at(i));
        stream << *pcPtr;
    }

    stream << pdu.m_userInfoPDU;

    return stream;
}

DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAssociateRequest &pdu)
{
    DcmNetStream netStream(stream);
    DcmAAssociateRequest acc;

    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AAssociateRq && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();

        DcmSize read = 0;

        DcmUnsignedShort protocolVersion;
        stream>> protocolVersion;
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

        /*
            Normally we should have application context going first,
            then a bunch of presentation context items, followed
            by user info PDU. But here we do not care and read them in
            arbitrary order.
        */
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
            } else if (item->type() == DcmPDUType_PresentationContext) {
                DcmPresentationContext *context = dynamic_cast<DcmPresentationContext*>(item);
                Q_ASSERT(context);
                if (!context->isValid()) {
                    qWarning() << "Invalid presentation context received" << context->abstractSyntax().uid();
                }
                acc.addAndRetainPresentationContext(context);
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
