#include "widget.h"
#include "ui_widget.h"

#include "serialportobj.h"
#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pserialObj = new SerialPortObj("COM1",115200);
    m_pThread = new QThread;
    m_pserialObj->moveToThread (m_pThread);
    connect (m_pThread,SIGNAL(started()),
             m_pserialObj,SLOT(slotStartInit()));
    connect(qApp,SIGNAL(aboutToQuit()),
            m_pserialObj,SLOT(deleteLater()));
    connect (m_pserialObj,SIGNAL(destroyed(QObject*)),
             m_pThread,SLOT(quit()));

//    connect (m_pThread,SIGNAL(finished()),
//             m_pThread,SLOT(deleteLater()));

    m_pThread->start ();

    connect (m_pserialObj,SIGNAL(signalSendSerialPortData(QByteArray)),
             this,SLOT(slotReadSerialData(QByteArray)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    //
}

void Widget::slotReadSerialData(const QByteArray &buff)
{
    qDebug ()<<buff;
}
