#ifndef SERIALPORTOBJ_H
#define SERIALPORTOBJ_H

#include <QObject>

#include "serialport_src/qextserialport.h"

class SerialPortObj : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortObj(const QString &portName,
                           const int portBaud,
                           QObject *parent = 0);
    ~SerialPortObj();

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

private Q_SLOTS:

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
    QString m_serialName;           //串口名称
    int m_serialBaud;               //波特率
};

#endif // SERIALPORTOBJ_H
