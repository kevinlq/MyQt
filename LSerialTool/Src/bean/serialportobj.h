#ifndef SERIALPORTOBJ_H
#define SERIALPORTOBJ_H

#include <QObject>

#include "serialport_src/qextserialport.h"

struct SerialInfo;

class SerialPortObj : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortObj(QObject *parent = 0);
    ~SerialPortObj();

    void setSerialName(const QString &name);

    void setSerialBaud(const int &baud);

    void setParity(const int &index);

    void setDataBits(const int &bit);

    void setStopBits(const float &bit);

    void setFlowControl(const int &flag);

    bool openSerial();

    bool getSerialStaus();

    bool closeSerial();

private:
    void init();

    BaudRateType getBaundRate(int number);

Q_SIGNALS:
    /**
     * @brief  :   用来将读取串口的数据通过信号发射出去
     * @param  :   数据接入方式，这里为1(串口)
     * @param  :   buffData 串口接收到的数据
     * @return :
     */
    void signalSendSerialPortData(const QByteArray &buff);

public Q_SLOTS:

    /**
      *@brief 初始化串口信息，外部线程start信号触发
    */
    void slotStartInit();

    /**
     * @brief  :   读取串口数据
     * @return :   void
     */
    void slotReadSerialPortData();

    /**
     * @brief  :   用来向串口写入数据
     * @param  :   buffData 待写入的数据
     * @return :   void
     */
    void slotWriteSerialPort(const QByteArray &buffData);

private:
    QextSerialPort  *m_pSerialPort; //串口指针

    SerialInfo  *d_ptr;
};

#endif // SERIALPORTOBJ_H
