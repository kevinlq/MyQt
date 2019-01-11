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
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include "DcmStream.h"
#include "DcmNetStream.h"
#include "DcmWriter.h"
#include "DcmPDUMaxLength.h"
#include "DcmPDVItem.h"
#include "DcmPDataTf.h"
#include "DcmCommunicator.h"

const int DcmCommunicator::DefaultTimeout = 30000;  // in ms.

DcmCommunicator::DcmCommunicator()
{
    m_socketPtr = new QTcpSocket();
    m_dataStreamPtr = new QDataStream(m_socketPtr);
    m_timeout = DcmCommunicator::DefaultTimeout;
    m_status = DcmCommunicator::Status_Ok;
    m_pduMaxLength = DcmPDUMaxLength::Default.length();
}

DcmCommunicator::DcmCommunicator(int socketHandle, int timeout)
{
    m_socketPtr = new QTcpSocket();
    m_socketPtr->setSocketDescriptor(socketHandle);
    m_dataStreamPtr = new QDataStream(m_socketPtr);
    m_timeout = timeout;
    m_status = DcmCommunicator::Status_Ok;
    m_pduMaxLength = DcmPDUMaxLength::Default.length();
}

DcmCommunicator::DcmCommunicator(QTcpSocket *socketPtr, int timeout)
{
    Q_ASSERT(socketPtr);
    m_socketPtr = socketPtr ? socketPtr : new QTcpSocket();
    m_dataStreamPtr = new QDataStream(m_socketPtr);
    m_timeout = timeout;
    m_status = DcmCommunicator::Status_Ok;
    m_pduMaxLength = DcmPDUMaxLength::Default.length();
}

DcmCommunicator::~DcmCommunicator()
{
    delete m_dataStreamPtr;
    delete m_socketPtr;
}

void DcmCommunicator::connectToHost(const QString &hostName, int port)
{
    m_socketPtr->connectToHost(hostName, port);
}

void DcmCommunicator::close()
{
    if (m_socketPtr->isOpen()) {
        m_socketPtr->close();
    }
}

int DcmCommunicator::socketHandle() const
{
    return m_socketPtr->socketDescriptor();
}

QTcpSocket* DcmCommunicator::socket()
{
    return m_socketPtr;
}

QDataStream* DcmCommunicator::dataStream()
{
    return m_dataStreamPtr;
}

int DcmCommunicator::timeout() const
{
    return m_timeout;
}

void DcmCommunicator::setTimeout(int t)
{
    m_timeout = t;
}

DcmSize DcmCommunicator::pduMaxLength() const
{
    return m_pduMaxLength;
}

void DcmCommunicator::setPduMaxLength(DcmSize length)
{
    if (length < 16) {
        m_pduMaxLength = DcmPDUMaxLength::Default.length();
        qWarning() << "PDU maximal length of" << length << "is too small. Defaultinh to" << m_pduMaxLength;
    } else {
        m_pduMaxLength = length;
    }
}

DcmCommunicator::Status DcmCommunicator::status() const
{
    return m_status;
}

QByteArray DcmCommunicator::receivePDUByteArray()
{
    char pduId[2];
    DcmSize length = 0;

    if (bytesAvailable() < 6) {
        setStatus(DcmCommunicator::Status_NoData);
        return QByteArray();
    }

    if (m_dataStreamPtr->readRawData(pduId, 2) != 2) {
        setStatus(DcmCommunicator::Status_IOError);
        return QByteArray();
    }

    if (!DcmPDUItem((DcmPDUType)pduId[0]).isAssociationLevel()) {
        setStatus(DcmCommunicator::Status_ProtocolError);
        return QByteArray();
    }

    *m_dataStreamPtr >> length;
    if (length == 0) {
        setStatus(DcmCommunicator::Status_ProtocolError);
        return QByteArray();
    }

    // Waiting for the data packet
    while (bytesAvailable() <  length) {
        if (!waitForReadyRead()) {
            setStatus(DcmCommunicator::Status_Timeout);
            return QByteArray();
        }
    }

    QByteArray data = m_dataStreamPtr->device()->read(length);
    if ((DcmSize)data.size() != length) {
        setStatus(DcmCommunicator::Status_IOError);
        return QByteArray();
    }

    // Reconstruct the initial packet
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream.writeRawData(pduId, 2);
    stream << length;
    array.append(data);

    setStatus(DcmCommunicator::Status_Ok);
    return array;
}

void DcmCommunicator::sendPDUByteArray(const QByteArray &byteArray)
{
    if (!m_socketPtr->isOpen()) {
        return;
    }

    quint64 written = m_dataStreamPtr->device()->write(byteArray);
    if (written != (quint64)byteArray.size()) {
        // Wait for data to be trasnmitted
        if (!waitForBytesWritten()) {
            setStatus(DcmCommunicator::Status_Timeout);
            return;
        }
    }

    setStatus(DcmCommunicator::Status_Ok);
}

DcmPDUItem* DcmCommunicator::receivePDUItem()
{
    DcmPDUItem *itemPtr = 0;

    QByteArray data = receivePDUByteArray();
    if (status() != DcmCommunicator::Status_Ok) {
        return 0;
    }

    DcmStream stream(data);
    DcmNetStream netStream(stream);

    itemPtr = netStream.readPDUItem();
    if (!itemPtr) {
        setStatus(DcmCommunicator::Status_ProtocolError);
        return 0;
    }

    setStatus(DcmCommunicator::Status_Ok);
    return itemPtr;
}

void DcmCommunicator::sendPDUItem(const DcmPDUItem &pdu)
{
    QByteArray data;

    DcmStream stream(&data, QIODevice::WriteOnly);
    DcmNetStream netStream(stream);
    netStream.writePDUItem(pdu);

    sendPDUByteArray(data);
}

void DcmCommunicator::sendPData(const QByteArray &data, int contextId, bool command)
{
    DcmSize chunkSize = m_pduMaxLength - 12;    // account for header stuff
    Q_ASSERT(chunkSize > 0);

    DcmSize sent = 0;
    while (sent < (DcmSize)data.size()) {
        DcmSize toSend = data.size() - sent;
        bool terminating = true;
        if (toSend > chunkSize) {
            terminating = false;
            toSend = chunkSize;
        }

        DcmPDVItem pdv(contextId, command, terminating);
        pdv.setByteArray(data.mid(sent, toSend));

        DcmPDataTf pdu;
        pdu.addPDV(pdv);

        sendPDUItem(pdu);
        sent += toSend;

        if (status() != DcmCommunicator::Status_Ok) {
            break;
        }
    }
}

void DcmCommunicator::sendDataset(DcmDataset &dataset,
                                  int contextId,
                                  bool command,
                                  const DcmTransferSyntax &syntax)
{
    QByteArray data;
    DcmStream stream(&data, QIODevice::WriteOnly, syntax);
    DcmWriter writer(&stream);
    // Ignore meta-info data
    writer.setIgnoreMetaInfoHeader(true);
    writer.writeDataset(dataset);

    sendPData(data, contextId, command);
}

void DcmCommunicator::sendDimseMessage(const DcmDimseMessage &message, int contextId)
{
    DcmDataset dataset = message.constCommandDataset();
    sendDataset(dataset,
                contextId,
                true,   // This is a command, so we enable command flag
                DcmTransferSyntax::ImplicitLittleEndian);
}

void DcmCommunicator::setStatus(DcmCommunicator::Status s)
{
    m_status = s;
}

quint64 DcmCommunicator::bytesAvailable()
{
    return m_dataStreamPtr->device()->bytesAvailable();
}

bool DcmCommunicator::waitForReadyRead()
{
    return m_dataStreamPtr->device()->waitForReadyRead(m_timeout);
}

bool DcmCommunicator::waitForBytesWritten()
{
    return m_dataStreamPtr->device()->waitForBytesWritten(m_timeout);
}
