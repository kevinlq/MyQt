#include "workdaatathread.h"

#include "messagequeue.h"

#include <QDebug>

WorkDaataThread::WorkDaataThread(QObject *parent):
    QThread(parent)
{
    m_bIsRunning = false;
    m_pMsgQueue = NULL;
}

WorkDaataThread::~WorkDaataThread()
{
    qDebug()<<"delete WorkDaataThread";
}

void WorkDaataThread::startThread()
{
    if ( !isRunning ())
    {
        setRuningFlag (true);

        start ();
    }
}

void WorkDaataThread::waitForFinished()
{
    if ( isRunning ())
    {
        setRuningFlag (false);
        wait (10);
    }
}

void WorkDaataThread::setMessgQueue(MessageQueue *pMsg)
{
    if ( pMsg != NULL )
    {
        m_pMsgQueue = pMsg;
    }
}

void WorkDaataThread::run()
{
    qDebug()<<"====WorkDaataThread start";

    QString buffer = "";
    while (getRunningFlag ())
    {
        buffer = m_pMsgQueue->dequeue ();
        if ( buffer.isEmpty ())
        {
            msleep (4);
            continue;
        }
        //deal with data.....
        emit signalMsg (buffer);
    }
}

bool WorkDaataThread::getRunningFlag()
{
    QMutexLocker locker(&m_mutex);
    return m_bIsRunning;
}

void WorkDaataThread::setRuningFlag(bool bRun)
{
    QMutexLocker locker(&m_mutex);
    m_bIsRunning = bRun;
}

