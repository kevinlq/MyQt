#include "widget.h"
#include "ui_widget.h"

#include "serialportobj.h"

#include <QDateTime>
#include <QDebug>

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
    this->setWindowTitle("串口助手");

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
}

void Widget::initObj()
{
    m_pSerialObj = new SerialPortObj(this);

    connect(m_pSerialObj,SIGNAL(signalSendSerialPortData(QByteArray)),
            this,SLOT(slotReceSerial(QByteArray)));
}

void Widget::slotReceSerial(const QByteArray &buf)
{
    ui->txtRecData->append(buf);
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

            //改变控件状态
            setSerialConEnable(false);
        }
    }else{
        if( m_pSerialObj->closeSerial()){
            ui->btnOpen->setText("打开");

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
    QByteArray tempBuff = ui->txtSend->text().toAscii();
    if (tempBuff.isEmpty())
        return;

    if (!m_pSerialObj->getSerialStaus())
        return ;

    m_pSerialObj->slotWriteSerialPort(tempBuff);

    if (ui->chShowSend->isChecked()){
        ui->txtRecData->append("【send】"+tempBuff);
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

void Widget::on_pbn_clearRece_clicked()
{
    ui->txtRecData->clear();
}

void Widget::on_pbn_clearSend_clicked()
{
    ui->txtSend->clear();
}

void Widget::on_chFileSend_clicked(bool checked)
{
    if (checked){
        ui->chFileSend->setChecked(true);
        //
    }
}
