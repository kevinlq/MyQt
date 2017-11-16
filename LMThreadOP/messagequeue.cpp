#include "messagequeue.h"

MessageQueue::MessageQueue()
{

}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::enqueue(QString data)
{
    QMutexLocker locker(&m_mutex);
    m_datas.enqueue (data);
}

QString MessageQueue::dequeue()
{
    QMutexLocker locker(&m_mutex);
    return m_datas.empty ()?NULL :m_datas.dequeue ();
}
