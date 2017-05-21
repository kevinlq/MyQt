/****************************************************************************
**
** Date    		: 2017-01-20
** Author  		: KevinLi
** E-Mail  		: kevinlq0912@163.com
** QQ      		: 2313828706
** Version 		: V1.0
** Description	:This file as client,receive data from server
** If you have any questions , please contact me
**
****************************************************************************/
#include "readfromtcpserver.h"

/*Qt socket*/
#include <QTcpSocket>
#include <QTimer>

#include <QThread>


ReadFromTcpServer::ReadFromTcpServer(const QString &ip, int port, bool isRconn, QObject *parent) :
    QObject(parent),m_serverIp(ip),m_serverPort(port),m_isRconnect(isRconn)
{
    //init();
}

ReadFromTcpServer::ReadFromTcpServer(QObject *parent):
    QObject(parent)
{
    //init();
}

ReadFromTcpServer::~ReadFromTcpServer()
{
    emit signalFinished();

    qDebug ()<<"destroy ReadFromTcpServer";
}

QString ReadFromTcpServer::getTcpConnectInfo() const
{
    return m_errorInfo;
}

void ReadFromTcpServer::init()
{
    this->initClient();

    this->initConnect();
}

void ReadFromTcpServer::initClient()
{
    initTimer();

    m_pTcpClinet = new QTcpSocket(this);
    m_pTcpClinet->abort();

    m_errorInfo.clear();
}

void ReadFromTcpServer::initTimer()
{
    m_pRConTimer = new QTimer(this);
    m_pRConTimer->setInterval(5000);
}

void ReadFromTcpServer::initConnect()
{
    connect(m_pTcpClinet,SIGNAL(readyRead()),
            this,SLOT(slotReceiveData()));

    connect(m_pTcpClinet,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(slotlSocetError(QAbstractSocket::SocketError)));

    /*Connect timoOut slot*/
    connect(m_pRConTimer,SIGNAL(timeout()),
            this,SLOT(slotTimeout()));
}

//线程开启时创建socket连接
void ReadFromTcpServer::slotStart()
{
    qDebug()<<"ReadFromTcpServer thread id:"<<QThread::currentThreadId();

    init ();

    slotConnectHost(true,m_serverIp,m_serverPort);
}


void ReadFromTcpServer::slotReceiveData()
{
    if (m_pTcpClinet->bytesAvailable() <= 0)
        return;
    QByteArray buff = m_pTcpClinet->readAll();
#ifdef DEBUG_OUT
    qDebug()<<"read from tpc server:"<<buff;
#endif

    emit signalSendData(buff,2);
}

/**
 *This function will ReConnected to server if Rcon is true
 *if false,The timer will stop
*/
void ReadFromTcpServer::slotRConnectServer(bool Rcon)
{
    if (Rcon)
    {
        if (!m_pRConTimer->isActive())
            m_pRConTimer->start();
    }else
    {
        if (m_pRConTimer->isActive())
            m_pRConTimer->stop();
    }
}

/**
 *slotTimeout will ReConnection Tcp server until the connection is ok
*/
void ReadFromTcpServer::slotTimeout()
{
    m_pTcpClinet->abort();

    if (!m_isConnect){
        m_pTcpClinet->connectToHost(m_serverIp,m_serverPort);
        if (m_pTcpClinet->waitForConnected(1000)){
            m_pRConTimer->stop();
            m_isConnect = true;
#ifdef DEBUG_OUT
            qDebug()<<"RConnect is ok!";
#endif
        }
        else{
            m_isConnect = false;
#ifdef DEBUG_OUT
            qDebug()<<"RConnect is failed!";
#endif
        }
    }
}

void ReadFromTcpServer::slotlSocetError(QAbstractSocket::SocketError)
{
    m_errorInfo = m_pTcpClinet->errorString();

    emit signalTcpConnectError(m_errorInfo);

    if (m_isRconnect)
        m_pRConTimer->start ();
}


void ReadFromTcpServer::slotConnectHost(bool isCon, const QString &ip, int port)
{
    if (isCon)
    {
        m_pTcpClinet->connectToHost(ip,port);

        if (!m_pTcpClinet->waitForConnected(1000))
        {
            m_isConnect = false;
            m_errorInfo = QString::fromLocal8Bit("连接失败!\r\n")+ m_pTcpClinet->errorString();
            if (m_isRconnect)
                m_pRConTimer->start ();
#ifdef DEBUG_OUT
            qDebug()<<"Connected failed!"<<m_errorInfo<<endl;
#endif
        }else{
            m_isConnect = true;
            m_errorInfo = QString::fromLocal8Bit("连接服务器成功!");
#ifdef DEBUG_OUT
            qDebug()<<"Connected ok!";
#endif
        }
    }else{
        m_pTcpClinet->disconnectFromHost();
        if (m_pTcpClinet->state() == QAbstractSocket::UnconnectedState ||
                m_pTcpClinet->waitForDisconnected(1000))
        {
            m_isConnect = false;
            m_errorInfo = QString::fromLocal8Bit("断开服务器成功!");
#ifdef DEBUG_OUT
            qDebug()<<"disconnect ok!";
#endif
        }
    }
}
