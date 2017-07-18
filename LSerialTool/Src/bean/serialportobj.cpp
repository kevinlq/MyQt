#include "serialportobj.h"
#include "serialinfo_p.h"

#include <QDebug>
#include <QThread>

SerialPortObj::SerialPortObj(QObject *parent)
    :QObject(parent)
{
    init();
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
    if (d_ptr){
        delete d_ptr;
        d_ptr = NULL;
    }
}

void SerialPortObj::setSerialName(const QString &name)
{
    if (!name.isEmpty())
        d_ptr->strName = name;
}

void SerialPortObj::setSerialBaud(const int &baud)
{
    if (baud < 0)
        return;
    d_ptr->baud = baud;
}

void SerialPortObj::setParity(const int &index)
{
    if (index < 0)
        return;
    d_ptr->parity = index;
}

void SerialPortObj::setDataBits(const int &bit)
{
    if (bit < 0)
        return;
    d_ptr->dataBits = bit;
}

void SerialPortObj::setStopBits(const float &bit)
{
    if (bit < 0)
        return;
    d_ptr->stopBits = bit;
}

void SerialPortObj::setFlowControl(const int &flag)
{
    if (flag < 0)
        return;
    d_ptr->isFlowControl = flag;
}

bool SerialPortObj::openSerial()
{
#ifdef  Q_OS_WIN
    m_pSerialPort = new QextSerialPort(d_ptr->strName);
#else
    m_pSerialPort = new QextSerialPort("/dev/"+d_ptr->strName);
#endif
    connect (m_pSerialPort,SIGNAL(readyRead()),
             this,SLOT(slotReadSerialPortData()));

    //清空缓冲区
    m_pSerialPort->flush ();
    //设置波特率
    m_pSerialPort->setBaudRate (getBaundRate (d_ptr->baud));
    //设置数据位
    m_pSerialPort->setDataBits ((DataBitsType)d_ptr->dataBits);
    //设置校验位
    m_pSerialPort->setParity ((ParityType)d_ptr->parity);
    //设置停止位
    m_pSerialPort->setStopBits ((StopBitsType)d_ptr->stopBits);
    //设置无硬件流控制
    m_pSerialPort->setFlowControl ((FlowType)d_ptr->isFlowControl);
    m_pSerialPort->setTimeout (10);

    if (m_pSerialPort->open (QIODevice::ReadWrite)){
        qDebug ()<<"open serial port ok!";
        return true;
    }else{
        qDebug ()<<"open serial port failed!"<<m_pSerialPort->errorString ();
        return false;
    }
}

bool SerialPortObj::getSerialStaus()
{
    if (!m_pSerialPort)
        return false;

    return m_pSerialPort->isOpen();
}

bool SerialPortObj::closeSerial()
{
    if (!m_pSerialPort)
        return false;

    m_pSerialPort->close();
    return true;
}

void SerialPortObj::init()
{
    d_ptr = new SerialInfo;
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
    //qDebug ()<<"SerialPortObj thread id:"<<QThread::currentThreadId ();

    //init();
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
