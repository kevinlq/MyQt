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

#ifndef DCMCOMMUNICATOR_H
#define DCMCOMMUNICATOR_H

#include <qglobal.h>
#include <QByteArray>
#include "DcmTypes.h"
#include "DcmPDUItem.h"
#include "DcmDataset.h"
#include "DcmDimseMessage.h"
#include "DcmNetApi.h"

class QTcpSocket;
class QDataStream;

/*! DICOM network communication helper class.
 * This class provides some basic I/O operation used
 * by DICOM SCP and SCU instances.
 */
class DcmCommunicator
{
public:

    static const int DefaultTimeout;    ///< Default communication timeout.

    /**
     * Communicator internal status.
     * The status must be checked after each operation in order
     * to keep the DICOM I/O stream consistent.
     */
    typedef enum {
        Status_Ok,              ///< Everything is fine.
        Status_IOError,         ///< I/O error detected.
        Status_NoData,          ///< No data avaibale in stream.
        Status_ProtocolError,   ///< DICOM protocol is not respected.
        Status_Timeout          ///< Communication timeout.
    } Status;

    DcmCommunicator();
    DcmCommunicator(int socketHandle, int timeout = DcmCommunicator::DefaultTimeout);
    DcmCommunicator(QTcpSocket *socketPtr, int timeout = DcmCommunicator::DefaultTimeout);
    ~DcmCommunicator();
    void connectToHost(const QString &hostName, int port);
    void close();
    int socketHandle() const;
    QTcpSocket* socket();
    QDataStream* dataStream();

    DcmCommunicator::Status status() const;
    int timeout() const;
    void setTimeout(int t);
    DcmSize pduMaxLength() const;
    void setPduMaxLength(DcmSize length);

    QByteArray receivePDUByteArray();
    void sendPDUByteArray(const QByteArray &byteArray);
    DcmPDUItem* receivePDUItem();
    void sendPDUItem(const DcmPDUItem &pdu);
    void sendPData(const QByteArray &data, int contextId, bool command = false);
    void sendDataset(DcmDataset &dataset,
                     int contextId,
                     bool command,
                     const DcmTransferSyntax &syntax = DcmTransferSyntax::ImplicitLittleEndian);
    void sendDimseMessage(const DcmDimseMessage &message, int contextId);

    bool waitForBytesWritten();

private:

    Q_DISABLE_COPY(DcmCommunicator)

    void setStatus(DcmCommunicator::Status s);
    quint64 bytesAvailable();
    bool waitForReadyRead();

    QTcpSocket *m_socketPtr;            ///< Communication socket.
    QDataStream *m_dataStreamPtr;       ///< Communication data stream.
    int m_timeout;                      ///< I/O operations timeout.
    DcmCommunicator::Status m_status;   ///< Communication operation status.
    DcmSize m_pduMaxLength;             ///< Allowed PDU maximal size in bytes.
};

#endif // DCMCOMMUNICATOR_H
