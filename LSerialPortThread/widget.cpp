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

    qDebug()<<"main widget thread id:"<<QThread::currentThreadId();

    /*这里的串口信息可以从配置文件中获取，这里只是单独传递串口号和波特率，
     *  实际开发中可以将这些参数放入一个list中进行传递或者一个map
    */
    m_pserialObj = new SerialPortObj("COM2",115200);
    m_pThread = new QThread;
    m_pserialObj->moveToThread (m_pThread);
    connect (m_pThread,SIGNAL(started()),
             m_pserialObj,SLOT(slotStartInit()));

    connect(qApp,SIGNAL(aboutToQuit()),
            m_pserialObj,SLOT(deleteLater()));

    connect (m_pserialObj,SIGNAL(destroyed(QObject*)),
             m_pThread,SLOT(quit()));

    connect (m_pThread,SIGNAL(finished()),
             m_pThread,SLOT(deleteLater()));

    connect (m_pserialObj,SIGNAL(signalSendSerialPortData(QByteArray)),
             this,SLOT(slotReadSerialData(QByteArray)));

    m_pThread->start ();
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
