/****************************************************************************
**
** Date    		: 2017-02-17
** Author  		: KevinLi
** E-Mail  		: kevinlq0912@163.com
** QQ      		: 2313828706
** Version 		: V1.0
** Description	:this file is read data from serial port
** If you have any questions , please contact me
** http://blog.csdn.net/u013704336
** https://github.com/kevinlq
** https://git.oschina.net/kevinlq0912
**
****************************************************************************/
#include "readserialport.h"

#include <QTimer>
#include <QDebug>
#include <QThread>

ReadSerialPort::ReadSerialPort(QObject *parent)
    :QObject(parent)
{
    init ();
}

ReadSerialPort::ReadSerialPort(const QString &serialName,
                               const int serialPort, QObject *parent) :
    QObject(parent),m_serialName(serialName),m_serialPort(serialPort)
{
    init();
}

ReadSerialPort::~ReadSerialPort()
{
    emit signalFinished();

    qDebug ()<<"destroy ReadSerialPort";
}

QString ReadSerialPort::getSerialOpenInfo() const
{
    return m_SerialOpenInfo;
}

void ReadSerialPort::init()
{
    initForm();

    initSerial();

    initConnect();
}

void ReadSerialPort::initForm()
{
    //初始化串口打开标志位
    m_isOpenSerial = false;
}

void ReadSerialPort::initSerial()
{
    m_pTimerRead = new QTimer(this);
    m_pTimerRead->setInterval(100);
    connect(m_pTimerRead,SIGNAL(timeout()),this,SLOT(slotReadComData()));

    m_SerialOpenInfo.clear();
}

void ReadSerialPort::initConnect()
{
}

BaudRateType ReadSerialPort::getBaundRate(int number)
{
    BaudRateType baud;
    switch (number) {
    case 9600:
        baud = BAUD9600;
        break;
    case 38400:
        baud = BAUD38400;
        break;
    case 115200:
        baud = BAUD115200;
        break;
    default:
        baud = BAUD38400;
        break;
    }
    return baud;
}

void ReadSerialPort::slotStart()
{
    qDebug()<<"ReadSerialPort current thread id:"<<QThread::currentThreadId();

    //slotOpenSerial (true,m_serialName,m_serialPort);
}


void ReadSerialPort::slotReadComData()
{
    if (m_pMyCom->bytesAvailable() <= 0)
        return;

    QByteArray data = m_pMyCom->readLine();
    int dataLen = data.length();

    if (dataLen <= 0)
        return;
#ifdef DEBUG_OUT
    qDebug()<<dataLen<<data;
#endif
    emit signalReadSerialData(data);
}

void ReadSerialPort::slotWriteSerial(const QByteArray &buff)
{
    if (m_pMyCom && !buff.isEmpty ()){
        m_pMyCom->write (buff);
    }
}


void ReadSerialPort::slotOpenSerial(bool isOpen,
                                    const QString &name,
                                    int baudRate)
{
    if (isOpen)
    {
#ifdef  Q_OS_WIN
        if (m_pMyCom)
            m_pMyCom = new QextSerialPort(name);
#else
        m_pMyCom = new QextSerialPort("/dev/" + name);
#endif
        //        connect(m_pMyCom,SIGNAL(readyRead()),this,SLOT(slotReadComData()));
        m_isOpenSerial = m_pMyCom->open(QIODevice::ReadWrite);

        if (m_isOpenSerial){
            //清空缓冲区
            m_pMyCom->flush();
            //设置波特率
            m_pMyCom->setBaudRate(getBaundRate(baudRate));
            //设置数据位
            m_pMyCom->setDataBits(DATA_8);
            //设置校验位
            m_pMyCom->setParity(PAR_NONE);
            //设置停止位
            m_pMyCom->setStopBits(STOP_1);
            m_pMyCom->setFlowControl(FLOW_OFF);
            m_pMyCom->setTimeout(10);
            m_pTimerRead->start();
            m_SerialOpenInfo = QString::fromLocal8Bit("open serial ok\r\n")+name;
#ifdef DEBUG_OUT
            qDebug()<<m_SerialOpenInfo;
#endif
        }else{
            m_SerialOpenInfo = QString::fromLocal8Bit("open serial failed ")
                    + m_pMyCom->errorString();
#ifdef DEBUG_OUT
            qDebug()<<"serial open failed"<<m_SerialOpenInfo;
#endif
        }
    }else{
        m_pTimerRead->stop();
        m_pMyCom->close();
        m_isOpenSerial = false;
        m_SerialOpenInfo = QString::fromLocal8Bit("close seriap ")+name;
#ifdef DEBUG_OUT
        qDebug()<<m_SerialOpenInfo;
#endif
    }
}
