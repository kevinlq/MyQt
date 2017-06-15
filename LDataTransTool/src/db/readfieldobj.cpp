#include "readfieldobj.h"

#include "db/ConnectionPool.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QTime>

ReadFieldObj::ReadFieldObj(const QString &table,
                           const QString &field,
                           QObject *parent)
    : QObject(parent),m_table(table),m_field(field)
{
    init ();
}

ReadFieldObj::~ReadFieldObj()
{
}

void ReadFieldObj::setTablInfo(const QString &table, const QString &field)
{
    m_table = table;
    m_field = field;
}

void ReadFieldObj::init()
{
    //
}

void ReadFieldObj::slotStartReadDbField()
{
    QTime time;
    time.start();

    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QString sql = "SELECT " + m_field + " FROM " + m_table;

    qDebug()<<sql;

    QSqlQuery query(db);
    if (!query.exec(sql)){
        qDebug()<<"select ais data error!"<<query.lastError().text();
        return;
    }
    while (query.next()){
        emit signalSendDbField(query.value(0).toString());
    }

    Singleton<ConnectionPool>::getInstance().closeConnection(db);

    qDebug()<<"use:"<<time.elapsed()/1000.0<<" s";
}
