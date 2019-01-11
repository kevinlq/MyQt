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
#include <QTimer>
#include "DcmCEchoRequest.h"
#include "DcmAAbort.h"
#include "DcmAReleaseRequest.h"
#include "DcmPDataTf.h"
#include "DcmReader.h"
#include "DcmSCU.h"

DcmSCU::DcmSCU(QObject *parent)
    : QObject(parent),
      m_state(DcmSCU::State_NotConnected),
      m_id(0)
{
    m_communicatorPtr = new DcmCommunicator();
    QTcpSocket *sock = m_communicatorPtr->socket();

    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(sock, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(sock, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));

    m_dimseTimerPtr = new QTimer();
    connect(m_dimseTimerPtr, SIGNAL(timeout()), this, SLOT(onDimseTimeout()));

    m_presentationContextId = -1;
}

DcmSCU::~DcmSCU()
{
    delete m_dimseTimerPtr;
    delete m_communicatorPtr;
}

DcmSCU::State DcmSCU::state() const
{
    return m_state;
}

void DcmSCU::setState(DcmSCU::State s)
{
    if (m_state != s) {
        m_state = s;
        emit stateChanged();
    }
}

void DcmSCU::connectToSCP(const QString &hostName, int port)
{
    if (state() != DcmSCU::State_NotConnected) {
        qWarning() << "Cannot connect to" << hostName << ":" << port
                   << "- SCU is already connected";
        return;
    }

    m_communicatorPtr->connectToHost(hostName, port);
    QTimer::singleShot(m_communicatorPtr->timeout(), this, SLOT(onConnectionTimeout()));
}

void DcmSCU::close()
{
    m_communicatorPtr->close();
    setState(DcmSCU::State_NotConnected);
}

int DcmSCU::timeout() const
{
    return m_communicatorPtr->timeout();
}

void DcmSCU::setTimeout(int t)
{
    m_communicatorPtr->setTimeout(t);
}

void DcmSCU::sendAssociationRequest(const DcmAAssociateRequest &request)
{
    if (state() != DcmSCU::State_Connected) {
        qWarning() << "SCU state is invalid. Cannot send association request";
        return;
    }

    m_communicatorPtr->sendPDUItem(request);
    if (m_communicatorPtr->status() == DcmCommunicator::Status_Ok) {
        m_associateRequest = request;
        setState(DcmSCU::State_AssociationRequest);
        QTimer::singleShot(m_communicatorPtr->timeout(), this, SLOT(onAssociationTimeout()));
    } else {
        qWarning() << "SCU failed to send association request. Connection will be closed.";
        close();
    }

}

void DcmSCU::abortAssociation()
{
    if (m_state != State_NotConnected) {
        DcmAAbort abort;
        m_communicatorPtr->sendPDUItem(abort);
        m_communicatorPtr->waitForBytesWritten();
        emit associationAbort();
        close();
    }
}

void DcmSCU::releaseAssociation()
{
    if (m_state != State_NotConnected) {
        DcmAReleaseRequest release;
        m_communicatorPtr->sendPDUItem(release);
        setState(State_AssociationRelease);
    }
}

void DcmSCU::sendDimseCommand(DcmDimseMessage &message, int contextId)
{
    if (!transferSyntaxForAcceptedContextId(contextId).isValid()) {
        qWarning() << "DICOM SCU: context" << contextId << "has not been negociated.";
        return;
    }

    message.setMessageId(getNextMessageId());
    m_communicatorPtr->sendDimseMessage(message, contextId);
    if (m_communicatorPtr->status() == DcmCommunicator::Status_Ok) {
        setState(DcmSCU::State_DimseCommand);
        // Launch timer to detect DIMSE response timeout
        m_dimseTimerPtr->setInterval(m_communicatorPtr->timeout());
        m_dimseTimerPtr->setSingleShot(true);
    } else {
        qWarning() << "DICOM SCU failed to send DIMSE command. Connection will be closed.";
        close();
        emit dimseError();
    }
}

void DcmSCU::sendDimseDataset(DcmDataset &dataset, int contextId)
{
    DcmTransferSyntax syntax = transferSyntaxForAcceptedContextId(contextId);
    if (syntax.isValid()) {
        m_communicatorPtr->sendDataset(dataset, contextId, false, syntax);
    } else {
        qWarning() << "DICOM SCU failed to send data for presentation context"
                   << contextId << "since it has not been negociated.";
        close();
        emit dimseError();
    }
}

void DcmSCU::sendCEcho()
{
    DcmCEchoRequest cEchoRequest;

    int id = -1; // Presentation context id

    // Getting verification context id
    for (int i = 0; i < m_associateRequest.numberOfPresentationContexts(); i++) {
        DcmPresentationContext *pc = m_associateRequest.presentationContextAt(i);

        if (pc->abstractSyntax() == DcmAbstractSyntax::Verification) {
            id = pc->id();
        }
    }

    if (id < 0) {
        qWarning() << "Verification (C-ECHO) presentation context has not been proposed by association.";
        emit dimseError();
        return;
    }

    int aid = -1;

    // Check if the context has been accepted
    for (int i = 0; i < m_associateAccept.numberOfAcceptedPresentationContexts(); i++) {
        DcmAcceptedPresentationContext *apc = m_associateAccept.acceptedPresentationContextAt(i);
        if (apc->id() == id) {
            if (!apc->transferSyntax().isValid()) {
                qWarning() << "Accepted verification context has invalid transfer syntax";
                emit dimseError();
                return;
            }
            aid = id;
            break;
        }
    }

    if (aid < 0) {
        qWarning() << "Verification context has not been accepted by SCP.";
        emit dimseError();
        return;
    }

    sendDimseCommand(cEchoRequest, id);
}

DcmAAssociateRequest DcmSCU::associationRequest() const
{
    return m_associateRequest;
}

DcmAAssociateAccept DcmSCU::associationAccept() const
{
    return m_associateAccept;
}

DcmAAssociateReject DcmSCU::associationReject() const
{
    return m_associateReject;
}

const DcmDimseRequest& DcmSCU::dimseRequest() const
{
    return m_dimseRequest;
}

const DcmDimseResponse& DcmSCU::dimseResponse() const
{
    return m_dimseResponse;
}


int DcmSCU::getNextMessageId()
{
    return ++m_id;
}

int DcmSCU::messageId() const
{
    return m_id;
}

void DcmSCU::onSocketStateChange(QAbstractSocket::SocketState s)
{
    if (s == QAbstractSocket::ConnectedState) {
        // Reset messages counter
        m_id = 0;
        setState(DcmSCU::State_Connected);
    }
}

void DcmSCU::onSocketError(QAbstractSocket::SocketError error)
{
    emit socketError();
}

void DcmSCU::onSocketDisconnected()
{
    setState(DcmSCU::State_NotConnected);
}

void DcmSCU::onConnectionTimeout()
{
    if (state() == DcmSCU::State_NotConnected) {
        emit connectionTimeout();
    }
}

void DcmSCU::onAssociationTimeout()
{
    if (state() == DcmSCU::State_AssociationRequest) {
        // Any other state means that association request phase is passed
        emit associationTimeout();
    }
}

void DcmSCU::onDimseTimeout()
{
    emit dimseTimeout();
}

void DcmSCU::onDataAvailable()
{
    Q_ASSERT(m_communicatorPtr);

    bool receivingData = true;
    while (receivingData) {
        DcmPDUItem *pduItem = m_communicatorPtr->receivePDUItem();
        if (m_communicatorPtr->status() != DcmCommunicator::Status_Ok) {
            // Something wrong happend, close connection
            emit dimseError();
            close();
            delete pduItem;
            return;
        }

        /* Depending on current state we tread the received data */
        switch (state()) {
        case State_AssociationRequest:
            // Association request has been sent, we are waiting
            // for association response (accept or reject).
            if (pduItem->type() == DcmPDUType_AAssociateAc) {
                // Association has been accepted
                DcmAAssociateAccept *accept = dynamic_cast<DcmAAssociateAccept*>(pduItem);
                Q_ASSERT(accept);
                handleAssociationAccept(*accept);
            } else if (pduItem->type() == DcmPDUType_AAssociateRj) {
                // Association has been rejected
                DcmAAssociateReject *reject = dynamic_cast<DcmAAssociateReject*>(pduItem);
                Q_ASSERT(reject);
                handleAssociationReject(*reject);
            } else {
                // Invalid response
                emit dimseError();
                close();
                delete pduItem;
                return;
            }
            break;

        case State_AssociationAccept:
            // Association has been accepted, he only thing we cna expect in this
            // state is association abort.
            if (pduItem->type() == DcmPDUType_AAbort) {
                DcmAAbort *abort = dynamic_cast<DcmAAbort*>(pduItem);
                Q_ASSERT(abort);
                emit associationAbort();
                close();
            } else {
                emit dimseError();
                close();
                delete pduItem;
                return;
            }
            break;

        case State_DimseCommand:
        case State_DimseData:
            // Handle DIMSE data or command
            if (pduItem->type() == DcmPDUType_PData) {
                DcmPDataTf *pdata = dynamic_cast<DcmPDataTf*>(pduItem);
                Q_ASSERT(pdata);
                if (pdata->count() < 1) {
                    qWarning() << "Received P-DATA with no PDVs. Association will be aborted.";
                    emit dimseError();
                    abortAssociation();
                }

                DcmPDVItem *pdv = pdata->at(0);
                Q_ASSERT(pdv);

                m_pdvData.append(pdv->byteArray());

                if (m_presentationContextId == -1) {
                    m_presentationContextId = pdv->presentationContextId();
                }

                if (pdv->isTerminating()) {
                    handleDimseRawMessage(pdv->isCommand());
                    m_pdvData.clear();
                    m_presentationContextId = -1;
                } else {
                    if (m_presentationContextId != pdv->presentationContextId()) {
                        qWarning() << "Received PDV of presentation context" << pdv->presentationContextId()
                                   << "but" << m_presentationContextId << "is expected.";
                        emit dimseError();
                        abortAssociation();
                    }
                }
            } else {
                qWarning() << "SCU received invalid PDU when P-DATA is expected.";
                emit dimseError();
                abortAssociation();
            }

            break;

        case State_AssociationRelease:
            if (pduItem->type() != DcmPDUType_AReleaseRp) {
                qWarning() << "Unexpected PDU item received on association release";
            }
            receivingData = false;
            close();
            break;

        default:
            qWarning() << "Received unexpected data for current SCU state";
            close();
            break;
        }

        delete pduItem;

        /* We have to continue handling incoming data, however if there
         * is no enought, we return from this slot, expecting it will be called
         * once more data become available.
         */
        if (receivingData &&
                m_communicatorPtr->socket()->bytesAvailable() < 6) {
            receivingData = false;
        }

    }
}

DcmTransferSyntax DcmSCU::transferSyntaxForAcceptedContextId(int contextId)
{
    for (int i = 0; i < m_associateAccept.numberOfAcceptedPresentationContexts(); i++) {
        DcmAcceptedPresentationContext *contextPtr = m_associateAccept.acceptedPresentationContextAt(i);
        Q_ASSERT(contextPtr);
        if (contextPtr->id() == contextId) {
            return contextPtr->transferSyntax();
        }
    }
    return DcmTransferSyntax::Invalid;
}

void DcmSCU::handleAssociationAccept(const DcmAAssociateAccept &ac)
{
    m_associateAccept = ac;
    DcmPDUUserInfo userInfo = ac.userInfoPDU();
    DcmSize pduSize = userInfo.pduMaxLength();
    m_communicatorPtr->setPduMaxLength(pduSize);

    setState(DcmSCU::State_AssociationAccept);
    emit associationAccepted();
}

void DcmSCU::handleAssociationReject(const DcmAAssociateReject &rj)
{
    m_associateReject = rj;
    emit associationRejected();
    close();
}

void DcmSCU::handleDimseRawMessage(bool command)
{
    DcmStream stream(m_pdvData);
    DcmReader reader(&stream);

    if (command) {
        if (state() != State_DimseCommand) {
            qWarning() << "Command DIMSE was expected.";
            emit dimseError();
            abortAssociation();
            return;
        }

        stream.setTransferSyntax(DcmTransferSyntax::ImplicitLittleEndian);
        DcmDataset dataset = reader.readDataset();
        if (reader.isError()) {
            qWarning() << "Unable to pase DIMSE command dataset.";
            emit dimseError();
            abortAssociation();
            return;
        }

        DcmTag *tag = dataset.findTag(DcmTagKey::CommandField);
        if (!tag) {
            qWarning() << "Command tag expected but not found.";
            emit dimseError();
            abortAssociation();
            return;
        }

        int cmd = (DcmCommandType)tag->value().toInt();
        if (!(cmd & 0x8000)) {
            qWarning() << "Expected DIMSE command response, but request received instead.";
            emit dimseError();
            abortAssociation();
            return;
        }

        DcmDimseResponse response(dataset);
        if (response.responseMessageId() != messageId()) {
            qWarning() << "DIMSE response id" << messageId() << "expected, but"
                       << response.messageId() << "received instead.";
            abortAssociation();
            return;
        }

        if (response.hasData()) {
            setState(State_DimseData);
        } else {
            m_dimseTimerPtr->stop();

            if (response.status() != DcmDimseResponse::Status_Pending) {
                // If no more data expected, switch back to association accepted state.
                setState(State_AssociationAccept);
            }
        }

        m_dimseResponse = response;
        emit dimseCommandResponse();
    } else {
        // Data DIMSE received

        m_dimseTimerPtr->stop();

        if (state() != State_DimseData) {
            qWarning() << "No DIMSE data expected.";
            emit dimseError();
            abortAssociation();
            return;
        }

        int contextId = (m_presentationContextId - 1)/2;

        if (contextId >= m_associateRequest.numberOfPresentationContexts()) {
            qWarning() << "Presentation context id is out of range.";
            emit dimseError();
            abortAssociation();
            return;
        }

        DcmAcceptedPresentationContext *context = m_associateAccept.acceptedPresentationContextAt(contextId);
        Q_ASSERT(context);

        DcmTransferSyntax xferSyntax = context->transferSyntax();
        stream.setTransferSyntax(xferSyntax);

        DcmDataset dataset = reader.readDataset();
        if (reader.isError()) {
            qWarning() << "Unable to parse received DICOM dataset.";
            emit dimseError();
            associationAbort();
            return;
        }

        if (dimseResponse().status() == DcmDimseResponse::Status_Pending) {
            setState(State_DimseCommand);
        } else {
            setState(State_AssociationAccept);
        }

        emit dimseDataset(dataset);
    }
}
