#ifndef READSERIALPORT_H
#define READSERIALPORT_H

#include <QObject>

class QTimer;

#include "qextserialport.h"


class ReadSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit ReadSerialPort(QObject *parent = 0);
    ReadSerialPort(const QString &serialName,const int serialPort,
                            QObject *parent = 0);
    ~ReadSerialPort();

    bool getSerialStatus(){return m_isOpenSerial;}

    QString getSerialOpenInfo() const;

private:
    void init();

    void initForm();

    void initSerial();

    void initConnect();

    BaudRateType getBaundRate(int number);

Q_SIGNALS:
    void signalFinished();

    /**
     * @brief  :   用来将读取串口的数据通过信号发射出去
     * @param  :   数据接入方式，这里为1(串口)
     * @param  :   buffData 串口接收到的数据
     * @return :
     */
    void signalReadSerialData(QByteArray buffData);

public Q_SLOTS:
    void slotStart();

    void slotOpenSerial(bool isOpen,const QString &name,int baudRate);

    void slotReadComData();

    void slotWriteSerial(const QByteArray &buff);

private:
    QTimer          *m_pTimerRead;
    QextSerialPort  *m_pMyCom;
    bool            m_isOpenSerial;

    QString         m_SerialOpenInfo;
    QString         m_serialName;
    int             m_serialPort;
    
};

#endif // READSERIALPORT_H
