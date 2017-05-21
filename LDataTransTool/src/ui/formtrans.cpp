#include "formtrans.h"
#include "ui_formtrans.h"

#include <QDebug>
#include "dataInput/readserialport.h"

#include <QFileDialog>
#include <QFile>
#include <QTimer>

FormTrans::FormTrans(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTrans)
{
    ui->setupUi(this);

    init ();
}

FormTrans::~FormTrans()
{
    delete ui;
}

void FormTrans::init()
{
    initForm ();

    initWidget ();

    setSerialEnable (false);

    setTcpEnable (false);

    setUdpEnable (false);
}

void FormTrans::initForm()
{
    ui->progressBar_value->setRange (0,99);
    ui->progressBar_value->setValue (0);

#ifdef Q_OS_WIN
    for (int i = 1;i < 10; i++){
        ui->comboBox_serianlName->addItem ("COM" + QString::number (i));
    }
    QStringList baudList;
    baudList <<"9600"<<"38400"<<"115200";
    ui->comboBox_baud->addItems (baudList);

    QStringList proBit;
    proBit <<"NONE"<<"ODD"<<"EVEN"<<"MARK"<<"SPACE";
    ui->comboBox_paritybit->addItems (proBit);

    QStringList dataBit;
    dataBit <<"8"<<"7"<<"6"<<"5";
    ui->comboBox_databit->addItems (dataBit);

    QStringList stopBit;
    stopBit <<"1"<<"1.5"<<"2";
    ui->comboBox_stopbit->addItems (stopBit);
#endif
    m_fileIsOpen = false;
}

void FormTrans::initWidget()
{
    m_pSerial = new ReadSerialPort(this);
    connect (m_pSerial,SIGNAL(signalReadSerialData(QByteArray)),
             this,SLOT(slotReadSerial(QByteArray)));
    m_pTimer = new QTimer(this);
    connect (m_pTimer,SIGNAL(timeout()),
             this,SLOT(slotTimeOut()));
    m_pTimer->setInterval (500);
}

void FormTrans::setSerialEnable(bool flag)
{
    ui->comboBox_serianlName->setEnabled (flag);
    ui->comboBox_baud->setEnabled (flag);
    ui->comboBox_databit->setEnabled (flag);
    ui->comboBox_paritybit->setEnabled (flag);
    ui->comboBox_stopbit->setEnabled (flag);
    ui->tbnSerial->setEnabled (flag);
}

void FormTrans::setTcpEnable(bool flag)
{
    ui->checkBox_server->setEnabled (flag);
    ui->checkBox_client->setEnabled (flag);
    ui->lineEdit_tcpIp->setEnabled (flag);
    ui->lineEdit_tcpPort->setEnabled (flag);
    ui->tbnTcpConnect->setEnabled (flag);
}

void FormTrans::setUdpEnable(bool flag)
{
    ui->lineEdit_udpIp->setEnabled (flag);
    ui->lineEdit_udpPort->setEnabled (flag);
    ui->tbnUdpConnect->setEnabled (flag);
}

void FormTrans::slotReadSerial(const QByteArray &buff)
{
    qDebug ()<<buff;
}

void FormTrans::slotTimeOut()
{
    if (!m_listByte.isEmpty ())
    {
        m_pSerial->slotWriteSerial (m_listByte.takeFirst ());
    }else{
        m_pTimer->stop ();
        m_listByte.clear ();
    }
}

//发送数据
void FormTrans::on_tbn_send_clicked()
{

    if (!m_fileInfo.isEmpty ()){
        QFile file(m_fileInfo);
        if ( !file.open (QIODevice::ReadOnly))
        {
            qDebug ()<<"open file failed!";
            m_fileIsOpen = false;
        }
        qDebug ()<<"open ok";
        m_fileIsOpen = true;

        if ( !m_fileIsOpen)
            return;
        QTextStream txtInput(&file);
        QString lineStr;

        while (!txtInput.atEnd ()){
            lineStr = txtInput.readLine ();
            //qDebug ()<<lineStr;
            m_listByte.append (lineStr.toAscii ());
        }
        file.close ();
    }

    if (!m_pTimer->isActive ()){
        m_pTimer->start ();
    }
}

void FormTrans::on_checkBox_serial_toggled(bool checked)
{
    setSerialEnable (checked);
}

void FormTrans::on_checkBox_tcp_toggled(bool checked)
{
    setTcpEnable (checked);
}

void FormTrans::on_checkBox_udp_toggled(bool checked)
{
    setUdpEnable (checked);
}

void FormTrans::on_tbnSerial_clicked()
{
    QString name = ui->comboBox_serianlName->currentText ();
    int baud = ui->comboBox_baud->currentText ().toInt ();

    if (m_pSerial && !name.isEmpty () && baud > 0){
        if (!m_pSerial->getSerialStatus ()){
            m_pSerial->slotOpenSerial (true,name,baud);
            ui->tbnSerial->setText ("关闭串口");
        }else{
            ui->tbnSerial->setText ("打开串口");
            m_pSerial->slotOpenSerial (false,name,baud);
        }
    }
}


//查找文本数据路径
void FormTrans::on_tbn_find_clicked()
{
    QString info;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter("(*.txt)");
    if (dialog.exec()){
        info = dialog.selectedFiles().at(0);
    }
    ui->lineEdit_data_source->setText (info);

    m_fileInfo = info;

}
