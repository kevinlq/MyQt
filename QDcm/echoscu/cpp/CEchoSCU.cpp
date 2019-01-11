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

#include "DcmPDUMaxLength.h"
#include "DcmPDUImplementationClassUID.h"
#include "DcmPDUImplementationVersionName.h"
#include "CEchoSCU.h"
#include "DcmSCU.h"

CEchoSCU::CEchoSCU(QObject *parent)
    : QObject(parent)
{
    m_scuPtr = new DcmSCU();
    m_host = "";
    m_port = 104;
    m_callingAE = "QDCM-SCU";
    m_calledAE = "ANYSCP";

    connect(m_scuPtr, SIGNAL(associationAccepted()), this, SLOT(onAssociationAccepted()));
    connect(m_scuPtr, SIGNAL(associationRejected()), this, SLOT(onAssociationRejected()));
    connect(m_scuPtr, SIGNAL(associationTimeout()), this, SLOT(onAssociationTimeout()));
    connect(m_scuPtr, SIGNAL(stateChanged()), this, SLOT(onScuStateChange()));
    connect(m_scuPtr, SIGNAL(dimseCommandResponse()), this, SLOT(onDimseResponse()));
    connect(m_scuPtr, SIGNAL(socketError()), this, SLOT(onSocketError()));
    connect(m_scuPtr, SIGNAL(connectionTimeout()), this, SLOT(onConnectionTimeout()));
    connect(m_scuPtr, SIGNAL(dimseTimeout()), this, SLOT(onDimseResposeTimeout()));
    connect(m_scuPtr, SIGNAL(dimseError()), this, SLOT(onDimseError()));
}

CEchoSCU::~CEchoSCU()
{
    delete m_scuPtr;
}

void CEchoSCU::setHost(const QString &host)
{
    m_host = host;
}

void CEchoSCU::setPort(int port)
{
    m_port = port;
}

void CEchoSCU::setCallingAE(const QString &ae)
{
    m_callingAE = ae;
}

void CEchoSCU::setCalledAE(const QString &ae)
{
    m_calledAE = ae;
}

void CEchoSCU::perform()
{
    qDebug() << "Connecting to" << m_host << ":" << m_port;
    m_scuPtr->setTimeout(1000);
    m_scuPtr->connectToSCP(m_host, m_port);
}

void CEchoSCU::onScuStateChange()
{
    qDebug() << __FUNCTION__;
    DcmSCU::State state = m_scuPtr->state();
    if (state == DcmSCU::State_Connected) {
        requestAssociation();
    }
}

void CEchoSCU::onAssociationAccepted()
{
    qDebug() << __FUNCTION__;
    DcmAAssociateAccept accept = m_scuPtr->associationAccept();
    if (accept.numberOfAcceptedPresentationContexts() < 1) {
        qDebug() << "Presentation context has not been accepted by SCU.";
        releaseAssociation();
        return;
    }

    int verificationContextId = -1;

    for (int i = 0; i < accept.numberOfAcceptedPresentationContexts(); i++) {
        DcmAcceptedPresentationContext *accContextPtr = accept.acceptedPresentationContextAt(i);
        if (accContextPtr->isAccepted()) {
            if (accContextPtr->id() == 1) {
                verificationContextId = accContextPtr->id();
            }
        } else {
            qDebug() << "Presentation context" << accContextPtr->id()
                     << "has not been accepted. Reason:" << accContextPtr->reason();
        }
    }

    if (verificationContextId < 0) {
        releaseAssociation();
        return;
    }

    m_scuPtr->sendCEcho();
}

void CEchoSCU::onAssociationRejected()
{
    qDebug() << __FUNCTION__;
    qDebug() << m_scuPtr->associationReject().reasonAsString();

    m_scuPtr->close();
}

void CEchoSCU::onAssociationTimeout()
{
    qDebug() << __FUNCTION__;
    m_scuPtr->close();
}

void CEchoSCU::onDimseResponse()
{
    qDebug() << __FUNCTION__;
    if (m_scuPtr->dimseResponse().command() != DcmCommandType_CEchoResponse) {
        qDebug() << "Invalid DIMSE response received.";
    } else {
        DcmDimseResponse::Status status = m_scuPtr->dimseResponse().status();
        if (status == DcmDimseResponse::Status_Success) {
            qDebug() << "C-ECHO OK";
        } else {
            qDebug() << "C-ECHO error status:" << status;
        }
    }

    releaseAssociation();
}

void CEchoSCU::onSocketError()
{
    qDebug() << __FUNCTION__;
    m_scuPtr->close();
    emit over();
}

void CEchoSCU::onConnectionTimeout()
{
    qDebug() << "Timeout connecting to" << m_host << ":" << m_port;
    m_scuPtr->close();
    emit over();
}

void CEchoSCU::onDimseResposeTimeout()
{
    qDebug() << __FUNCTION__;
    releaseAssociation();
}

void CEchoSCU::onDimseError()
{
    qDebug() << __FUNCTION__;
    releaseAssociation();
}

void CEchoSCU::requestAssociation()
{
    DcmAAssociateRequest request;
    request.setApplicationContext(DcmApplicationContext::Default);
    request.setCallingAE(m_callingAE);
    request.setCalledAE(m_calledAE);

    DcmPresentationContext presentationContext(DcmAbstractSyntax::Verification);
    presentationContext.setId(1);   // 1st presentation context to negociate
    presentationContext.addTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
    presentationContext.addTransferSyntax(DcmTransferSyntax::ExplicitLittleEndian);

    DcmPDUUserInfo userInfo;
    DcmPDUMaxLength maxLength(16384);
    DcmPDUImplementationClassUID implementationClassUid("1.2.3.4.5.6.7.8");
    DcmPDUImplementationVersionName implementationVersion("QDCM-0.1");
    userInfo.append(maxLength);
    userInfo.append(implementationClassUid);
    userInfo.append(implementationVersion);

    request.setUserInfoPDU(userInfo);

    m_scuPtr->sendAssociationRequest(request);
}

void CEchoSCU::releaseAssociation()
{
    emit over();
}
