#include "appinittest.h"

#include "customthreadobject.h"

#include <QThread>
#include <QDebug>
#include <QTimer>

AppInitTest::AppInitTest(QObject *parent)
    : QObject(parent)
{

}

AppInitTest::~AppInitTest()
{
    if (m_pCusThreadObj)
    {
        delete m_pCusThreadObj;
        m_pCusThreadObj = NULL;
    }
    if (m_pThread)
    {
        if (m_pThread->isRunning())
        {
            m_pThread->quit();
            m_pThread->wait();
        }
        delete m_pThread;
        m_pThread = NULL;
    }
    if (m_pTimer){
        if (m_pTimer->isActive())
        {
            m_pTimer->stop();
        }
        delete m_pTimer;
        m_pTimer = NULL;
    }
}

void AppInitTest::init()
{
    m_pCusThreadObj = new CustomThreadObject;
    m_pThread = new QThread;
    m_pCusThreadObj->moveToThread(m_pThread);

    connect(m_pThread,SIGNAL(started()),m_pCusThreadObj,SLOT(slotStart()));
    connect(m_pThread,SIGNAL(finished()),m_pCusThreadObj,SLOT(deleteLater()));
    connect(m_pThread,SIGNAL(finished()),m_pThread,SLOT(deleteLater()));
    connect(this,SIGNAL(signalOperate()),m_pCusThreadObj,SLOT(slotDoWork()));
    connect(m_pCusThreadObj,SIGNAL(signalResultReady(int)),
            this,SLOT(slotHandleResults(int)),Qt::QueuedConnection);
    m_pThread->start();

    m_pTimer = new QTimer(this);
    connect(m_pTimer,SIGNAL(timeout()),this,SIGNAL(signalOperate()));
    m_pTimer->setInterval(100);
    m_pTimer->start();
}

void AppInitTest::slotHandleResults(const int value)
{
    qDebug()<<"value:"<<value;
}
