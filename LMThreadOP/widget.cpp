#include "widget.h"
#include "ui_widget.h"

#include <QTimer>
#include <QDateTime>

#include "workdaatathread.h"
#include "messagequeue.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval (100);
    connect (m_pTimer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));

    m_pMessageQueue = new MessageQueue;
    m_pWorkThread = new WorkDaataThread;
    m_pWorkThread->setMessgQueue (m_pMessageQueue);
//    m_pWorkThread->startThread ();
    connect (m_pWorkThread,SIGNAL(signalMsg(QString)),
             this,SLOT(slotRMsg(QString)));
}

Widget::~Widget()
{
    delete ui;

    if (m_pTimer != NULL)
    {
        delete m_pTimer;
        m_pTimer = NULL;
    }

    if (m_pMessageQueue != NULL)
    {
        delete m_pMessageQueue;
        m_pMessageQueue = NULL;
    }
    if (m_pWorkThread != NULL)
    {
        m_pWorkThread->waitForFinished ();
        delete m_pWorkThread;
        m_pWorkThread = NULL;
    }
}

void Widget::on_pbnStart_clicked()
{
    if ( !m_pTimer->isActive ())
    {
        m_pTimer->start ();

        m_pWorkThread->startThread ();
    }
}

void Widget::slotTimeOut()
{
    QString tim = QDateTime::currentDateTime ().toString ("yyyy-MM-dd hh:mm:ss:zzz");
    tim.append (ui->lineEdit->text ());
    ui->textEdit->append (tim);

    m_pMessageQueue->enqueue (tim);
}

void Widget::slotRMsg(const QString &msg)
{
    ui->textEdit_2->append (msg);
}
