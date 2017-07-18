#ifndef SERIALINFO_P_H
#define SERIALINFO_P_H

#include <QObject>

struct SerialInfo{
    QString strName;    //串口号
    int baud;           //波特率
    int parity;         //校验位
    int dataBits;       //数据位
    float stopBits;     //停止位/1,1.5,2
    int  isFlowControl; //硬件流控制是否
    int timeOut;        //10
};

#endif // SERIALINFO_P_H
