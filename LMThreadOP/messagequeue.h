#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QQueue>
#include <QMutex>

typedef QString QString;

class MessageQueue
{
public:
    MessageQueue();
    ~MessageQueue();

    void enqueue(QString);
    QString dequeue();
private:
    QMutex m_mutex;
    QQueue<QString> m_datas;
};

#endif // MESSAGEQUEUE_H
