#include "customthreadobject.h"

#include <QDebug>
#include <QThread>

CustomThreadObject::CustomThreadObject(QObject *parent) : QObject(parent)
{

}

CustomThreadObject::~CustomThreadObject()
{
    qDebug()<<"destroy CustomThreadObject!";
}

void CustomThreadObject::slotStart()
{
    qDebug()<<"CustomThreadObject thread id:"<<QThread::currentThreadId();
}

void CustomThreadObject::slotDoWork()
{
    static int count = 0;
    qDebug()<<count++;
}
