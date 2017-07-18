#include "widget.h"
#include "ui_widget.h"

#include "serialportobj.h"

#include <QDateTime>
#include <QDebug>

#include <QTimer>
#include <QFileDialog>

#define DATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    initForm();

    initObj();
}

void Widget::initForm()
{
    this->setWindowTitle("串口助手-devstone(kevinlq0912@163.com)");

    QStringList comList;//串口号
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位

    //串口号初始化
    comList.clear();
#ifdef  Q_OS_WIN
    comList<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"
          <<"COM7"<<"COM8"<<"COM9"<<"COM10"<<"COM11"<<"COM12"
         <<"COM13"<<"COM14"<<"COM15"<<"COM16"<<"COM17"<<"COM18"
        <<"COM19"<<"COM20"<<"COM21"<<"COM22"<<"COM23"<<"COM24"
       <<"COM25"<<"COM26"<<"COM27"<<"COM28"<<"COM28"<<"COM29"<<"COM30";
#else
    comList <<"ttyUSB0"<<"ttyUSB1"<<"ttyUSB2";
#endif
    ui->cboxPortName->clear();
    ui->cboxPortName->addItems(comList);
    ui->cboxPortName->setCurrentIndex(0);

    //波特率初始化
    baudList.clear();
    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
           <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
          <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
         <<"76800"<<"115200"<<"128000"<<"256000";
    ui->cboxBaudRate->clear();
    ui->cboxBaudRate->addItems(baudList);
    ui->cboxBaudRate->setCurrentIndex(15);

    //校验位
    parityList.clear();
    parityList<<"无"<<"奇"<<"偶"<<"标志"<<"空格";
    ui->cboxParity->clear();
    ui->cboxParity->addItems(parityList);
    ui->cboxParity->setCurrentIndex(0);

    //数据位
    dataBitsList.clear();
    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->cboxDataBit->clear();
    ui->cboxDataBit->addItems(dataBitsList);
    ui->cboxDataBit->setCurrentIndex(3);

    //停止位
    stopBitsList.clear();
    stopBitsList<<"1"<<"1.5"<<"2";
    ui->cboxStopBit->clear();
    ui->cboxStopBit->addItems(stopBitsList);
    ui->cboxStopBit->setCurrentIndex(0);

    //发送区
    for(int i = 100;i < 1001;i+=100){
        ui->cboxTime->addItem(QString::number(i));
    }
    ui->cboxTime->setEditable(true);

    //更新时间
    m_pUpdateTime = new QTimer(this);
    connect(m_pUpdateTime,SIGNAL(timeout()),
            this,SLOT(slotUpdateTime()));
    m_pUpdateTime->start(1000);

    m_pAutoSendTime = new QTimer(this);
    connect(m_pAutoSendTime,SIGNAL(timeout()),
            this,SLOT(slotAutoSendInfo()));
    m_pAutoSendTime->setInterval(ui->cboxTime->currentText().toInt());

    m_fileConList.clear();

    m_sendCount = 0;
    m_receCount = 0;
}

void Widget::initObj()
{
    m_pSerialObj = new SerialPortObj(this);

    connect(m_pSerialObj,SIGNAL(signalSendSerialPortData(QByteArray)),
            this,SLOT(slotReceSerial(QByteArray)));
}

/**
  接收串口信息
*/
void Widget::slotReceSerial(const QByteArray &buf)
{
    this->setShowText(buf);
    m_receCount += buf.size();
    ui->labReceive->setText(QString("接收:%1 字节").arg(m_receCount));
}

void Widget::slotUpdateTime()
{
    ui->labDate->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    ui->labTime->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void Widget::slotAutoSendInfo()
{
    static int index = 0;
    QByteArray sendBuff;
    if (!m_pSerialObj->getSerialStaus())
        return ;
    if (index ==  (m_fileConList.count() - 1)){
        m_pAutoSendTime->stop();
        ui->btnSend->setText("发送");
        setSendAreaEnable(true);
        index = 0;
        return;
    }
    sendBuff = m_fileConList.at(index).toAscii();

    m_pSerialObj->slotWriteSerialPort(sendBuff);

    m_sendCount += sendBuff.size();
    ui->labSend->setText(QString("发送:%1 字节").arg(m_sendCount));

    if (ui->chShowSend->isChecked())
        this->setShowText(sendBuff);
    index++;
}

/**
  打开串口
*/
void Widget::on_btnOpen_clicked()
{
    if (ui->btnOpen->text() == QString("打开")){
        m_pSerialObj->setSerialName(ui->cboxPortName->currentText());
        m_pSerialObj->setSerialBaud(ui->cboxBaudRate->currentText().toInt());
        m_pSerialObj->setDataBits(ui->cboxDataBit->currentText().toInt());
        m_pSerialObj->setParity(ui->cboxParity->currentIndex());
        m_pSerialObj->setStopBits(ui->cboxStopBit->currentIndex());
        m_pSerialObj->setFlowControl(0);

        if (m_pSerialObj->openSerial()){
            ui->btnOpen->setText("关闭");
            ui->labIsOpen->setText("串口状态:打开");

            //改变控件状态
            setSerialConEnable(false);
        }
    }else{
        if( m_pSerialObj->closeSerial()){
            ui->btnOpen->setText("打开");
            ui->labIsOpen->setText("串口状态:关闭");

            //改变控件状态
            setSerialConEnable(true);
        }
    }
}

/**
  发送数据
*/
void Widget::on_btnSend_clicked()
{
    QByteArray tempBuff;
    if (ui->btnSend->text() == "发送")
    {
        ui->btnSend->setText("停止发送");
        //如果是自动发送
        if ( ui->ckIsAutoSend->isChecked()){
            //开启定时器发送数据
            if (!m_pAutoSendTime->isActive())
                m_pAutoSendTime->start();

            setSendAreaEnable(false);
        }else
        {
            if (!m_pSerialObj->getSerialStaus())
                return ;

            tempBuff = ui->txtSend->toPlainText().toAscii();
            if (tempBuff.isEmpty())
                return;

            //将数据写入串口缓冲区
            m_pSerialObj->slotWriteSerialPort(tempBuff);
            m_sendCount += tempBuff.size();
            ui->labSend->setText(QString("发送:%1 字节").arg(m_sendCount));

            //显示已经发送的数据
            if (ui->chShowSend->isChecked()){
                ui->txtRecData->append("【send】"+tempBuff);
            }
        }

    }else if (ui->btnSend->text() == "停止发送")
    {
        ui->btnSend->setText("发送");

        m_pAutoSendTime->stop();

        setSendAreaEnable(true);
    }

}

void Widget::setSerialConEnable(const bool &flag)
{
    ui->cboxBaudRate->setEnabled(flag);
    ui->cboxDataBit->setEnabled(flag);
    ui->cboxParity->setEnabled(flag);
    ui->cboxPortName->setEnabled(flag);
    ui->cboxStopBit->setEnabled(flag);
}

void Widget::setSendAreaEnable(const bool &flag)
{
    ui->gbox3->setEnabled(flag);
}

void Widget::setShowText(const QString &txt)
{
    if (txt.isEmpty())
        return;
    QString str;
    if (ui->chShowSendTime->isChecked()){
        str.append("[");
        str.append(DATETIME);
        str.append("]");
        str.append(txt);
    }
    if (ui->chAutoNewLine->isChecked()){
        str.append("\r\n");
    }
    ui->txtRecData->append(str);
}

void Widget::setShowText(const QByteArray &txt)
{
    if (txt.isEmpty())
        return;
    QString str;
    if (ui->chShowSendTime->isChecked()){
        str.append("[");
        str.append(DATETIME);
        str.append("]");
        str.append(txt);
    }
    if (ui->chAutoNewLine->isChecked()){
        str.append("\r\n");
    }
    ui->txtRecData->append(txt);
}

void Widget::on_pbn_clearRece_clicked()
{
    ui->txtRecData->clear();
    m_receCount = 0;
}

void Widget::on_pbn_clearSend_clicked()
{
    ui->txtSend->clear();
    m_sendCount = 0;
}

void Widget::on_chFileSend_clicked(bool checked)
{
    QString lineStr;
    m_fileConList.clear();
    QString info;
    QFileDialog dialog;

    if (checked)
    {
        dialog.setFileMode(QFileDialog::ExistingFiles);
        dialog.setViewMode(QFileDialog::Detail);
        dialog.setNameFilter("(*.txt)");
        if (dialog.exec()){
            info = dialog.selectedFiles().at(0);
        }
        if (info.isEmpty())
            return;

        QFile file(info);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        while (!in.atEnd()){
            lineStr = in.readLine();

            if (!lineStr.isEmpty())
                m_fileConList.append(lineStr);
        }

        file.close();
        ui->txtSend->setText("启用外部数据源\r\n"+info);
    }else{
        ui->txtSend->setText("http://kevinlq.com/");
    }
    ui->txtSend->setEnabled(checked);
#if 0
    for (int i = 0;i < m_fileConList.count();i++)
    {
        qDebug()<<m_fileConList.at(i);
    }
#endif
}

void Widget::on_cboxTime_activated(const QString &arg1)
{
    m_pAutoSendTime->setInterval(arg1.toInt());
}
