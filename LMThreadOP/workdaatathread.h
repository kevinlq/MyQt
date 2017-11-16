#ifndef WORKDAATATHREAD_H
#define WORKDAATATHREAD_H

#include <QThread>
#include <QMutexLocker>

class MessageQueue;

class WorkDaataThread : public QThread
{
    Q_OBJECT
public:
    WorkDaataThread(QObject *parent = Q_NULLPTR);
    ~WorkDaataThread();

    void startThread();

    void waitForFinished();

    void setMessgQueue(MessageQueue *pMsg);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    bool getRunningFlag();

    void setRuningFlag(bool bRun);

Q_SIGNALS:
    void signalMsg(const QString &);

private Q_SLOTS:

private:
    bool m_bIsRunning;
    QMutex m_mutex;
    MessageQueue *m_pMsgQueue;
};

#endif // WORKDAATATHREAD_H
