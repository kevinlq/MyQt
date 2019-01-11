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

#ifndef DCMSCU_H
#define DCMSCU_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "DcmNetApi.h"
#include "DcmCommunicator.h"
#include "DcmAAssociateRequest.h"
#include "DcmAAssociateAccept.h"
#include "DcmAAssociateReject.h"
#include "DcmDimseMessage.h"
#include "DcmDimseRequest.h"
#include "DcmDimseResponse.h"
#include "DcmDataset.h"

/*! DcmSCU
 * DICOM Basic client.
 */
class DCM_NET_API DcmSCU: public QObject
{
    Q_OBJECT

public:

    /**
     * SCU internal state.
     */
    typedef enum {
        State_NotConnected,         ///< SCU is not connected to any SCP.
        State_Connected,            ///< SCU is connected to SCP, but not associated.
        State_AssociationRequest,   ///< Association request sent.
        State_AssociationAccept,    ///< Association accepted.
        State_DimseCommand,         ///< Waiting for DIMSE command.
        State_DimseData,            ///< Waiting for DIMSE data.
        State_AssociationRelease    ///< Releasing association.
    } State;

    /**
     * Construct DICOM client.
     * \param parent Parent QObject.
     */
    DcmSCU(QObject *parent = 0);

    /**
     * Destructor.
     */
    ~DcmSCU();

    /**
     * Returns current state of the SCU.
     * \return SCU state.
     */
    DcmSCU::State state() const;

    /**
     * Perform connection to the SCP (server).
     * \param hostName SCP host name or IP address.
     * \param port TCP port number.
     */
    void connectToSCP(const QString &hostName, int port);


    /**
     * Close connection.
     */
    void close();

    /**
     * Send association request to SCP.
     * \param request Association request to be sent.
     */
    void sendAssociationRequest(const DcmAAssociateRequest &request);

    /**
     * Send DIMSE message to SCP.
     * The message will be updated with an id.
     * \param message DIMSE message to be sent.
     * \param contextId Context id.
     */
    void sendDimseCommand(DcmDimseMessage &message, int contextId);
    void sendDimseDataset(DcmDataset &dataset, int contextId);

    void sendCEcho();

    /**
     * Abort association.
     * This will send association abort message to SCP and
     * close connection.
     */
    void abortAssociation();
    void releaseAssociation();

    int timeout() const;
    void setTimeout(int t);

    DcmAAssociateRequest associationRequest() const;
    DcmAAssociateAccept associationAccept() const;
    DcmAAssociateReject associationReject() const;

    const DcmDimseRequest& dimseRequest() const;
    const DcmDimseResponse& dimseResponse() const;

signals:

    void connectionTimeout();
    void socketError();
    void associationTimeout();
    void dimseTimeout();
    void dimseError();
    void stateChanged();
    void associationAccepted();
    void associationRejected();
    void associationAbort();
    void dimseCommandResponse();
    void dimseDataset(const DcmDataset &dataset);

private slots:

    void onDataAvailable();
    void onSocketStateChange(QAbstractSocket::SocketState s);
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketDisconnected();
    void onConnectionTimeout();
    void onAssociationTimeout();
    void onDimseTimeout();

private:

    Q_DISABLE_COPY(DcmSCU)

    void setState(DcmSCU::State s);
    int getNextMessageId();
    int messageId() const;

    /**
     * Returns negociated transfer syntax for specified context ID.
     * If no context ID is found, Invalid transfer syntax is returned.
     * \param contextId Context ID.
     * \return Negociated transfer syntax.
     */
    DcmTransferSyntax transferSyntaxForAcceptedContextId(int contextId);

    void handleAssociationAccept(const DcmAAssociateAccept &ac);
    void handleAssociationReject(const DcmAAssociateReject &rj);

    /**
     * Process received raw DIMSE message.
     * This will parse received data into DICOM dataset.
     * \param command Set to true if a command received.
     */
    void handleDimseRawMessage(bool command);

    DcmSCU::State m_state;  ///< SCU state.

    DcmCommunicator *m_communicatorPtr; ///< Communicator object.

    int m_id;   ///< DIMSE message id.

    DcmAAssociateRequest m_associateRequest;
    DcmAAssociateAccept m_associateAccept;
    DcmAAssociateReject m_associateReject;

    DcmDimseRequest m_dimseRequest;
    DcmDimseResponse m_dimseResponse;

    int m_presentationContextId;    ///< Data presentation context.
    QByteArray m_pdvData;   ///< Raw data received.

    QTimer *m_dimseTimerPtr;
};

#endif // DCMSCU_H
