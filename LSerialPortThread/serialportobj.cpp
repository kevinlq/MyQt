#include "serialportobj.h"

#include <QDebug>
#include <QThread>

SerialPortObj::SerialPortObj(const QString &portName,
                             const int portBaud,
                             QObject *parent)
    :QObject(parent),m_serialName(portName),m_serialBaud(portBaud)
{
}

SerialPortObj::~SerialPortObj()
{
    qDebug ()<<"destroy SerialPortObj";
    if (m_pSerialPort){
        if (m_pSerialPort->isOpen ())
            m_pSerialPort->close ();
        delete m_pSerialPort;
        m_pSerialPort = NULL;
    }
}

void SerialPortObj::init()
{
#ifdef  Q_OS_WIN
    m_pSerialPort = new QextSerialPort(m_serialName);
#else
    m_pSerialPort = new QextSerialPort("/dev/"+m_serialName);
#endif
    connect (m_pSerialPort,SIGNAL(readyRead()),
             this,SLOT(slotReadSerialPortData()));

    //清空缓冲区
    m_pSerialPort->flush ();
    //设置波特率
    m_pSerialPort->setBaudRate (getBaundRate (m_serialBaud));
    //设置数据位
    m_pSerialPort->setDataBits (DATA_8);
    //设置校验位
    m_pSerialPort->setParity (PAR_NONE);
    //设置停止位
    m_pSerialPort->setStopBits (STOP_1);
    //设置无硬件流控制
    m_pSerialPort->setFlowControl (FLOW_OFF);
    m_pSerialPort->setTimeout (10);

    if (m_pSerialPort->open (QIODevice::ReadWrite)){
        qDebug ()<<"open serial port ok!";
    }else{
        qDebug ()<<"open serial port failed!"<<m_pSerialPort->errorString ();
    }
}

BaudRateType SerialPortObj::getBaundRate(int number)
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

void SerialPortObj::slotStartInit()
{
    qDebug ()<<"SerialPortObj thread id:"<<QThread::currentThreadId ();

    init();
}

void SerialPortObj::slotReadSerialPortData()
{
    if (m_pSerialPort->bytesAvailable () <= 0)
        return ;

    QByteArray tempBuf = m_pSerialPort->readAll ();

    emit signalSendSerialPortData (tempBuf);
}

void SerialPortObj::slotWriteSerialPort(const QByteArray &buffData)
{
    if (!buffData.isEmpty ())
        m_pSerialPort->write (buffData);
}
