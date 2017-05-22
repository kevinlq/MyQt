#ifndef READFROMTCPSERVER_H
#define READFROMTCPSERVER_H

#include <QObject>
#include <QAbstractSocket>


class QTcpSocket;
class QTimer;

class  ReadFromTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit ReadFromTcpServer(QObject *parent = 0);
    ReadFromTcpServer(const QString &ip,int port,bool isRconn,
                      QObject *parent = 0);
    ~ReadFromTcpServer();

    bool getTcpConnectStatus(){return m_isConnect;}

    QString getTcpConnectInfo()const;

private:
    void init();
    void initClient();
    void initTimer();
    void initConnect();
    
Q_SIGNALS:
    void signalFinished();

    void signalSendData(QByteArray buff,quint8 way);

    void signalTcpConnectError(const QString &error);

public Q_SLOTS:
    void slotStart();

    void slotConnectHost(bool isCon,const QString&ip,int port);

    void slotReceiveData();

    /*This file Rconnect to ais send server*/
    void slotRConnectServer(bool);

    void slotTimeout();

    void slotlSocetError(QAbstractSocket::SocketError);

private:
    QString m_serverIp;
    int m_serverPort;

    bool m_isConnect;
    bool m_isRconnect;          //是否断开连接后重新连接
    QTcpSocket *m_pTcpClinet;
    QTimer *m_pRConTimer;       /*Reconnect timer*/

    QString m_errorInfo;
    
};

#endif // READFROMTCPSERVER_H
