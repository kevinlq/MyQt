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

#ifndef CECHOSCU_H
#define CECHOSCU_H

#include <QObject>


class DcmSCU;

class CEchoSCU: public QObject
{
    Q_OBJECT

public:

    CEchoSCU(QObject *parent = 0);
    ~CEchoSCU();

    void setHost(const QString &host);
    void setPort(int port);
    void setCallingAE(const QString &ae);
    void setCalledAE(const QString &ae);

public slots:

    /// Perform C-Echo transaction
    void perform();

signals:

    void over();

private slots:

    void onScuStateChange();
    void onAssociationAccepted();
    void onAssociationRejected();
    void onAssociationTimeout();
    void onDimseResponse();
    void onSocketError();
    void onConnectionTimeout();
    void onDimseResposeTimeout();
    void onDimseError();

private:

    void requestAssociation();
    void releaseAssociation();

    DcmSCU *m_scuPtr;
    QString m_host;
    int m_port;
    QString m_callingAE;
    QString m_calledAE;
};

#endif // CECHOSCU_H
