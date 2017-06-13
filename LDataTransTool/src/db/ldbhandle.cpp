#include "ldbhandle.h"

#include "db/ConnectionPool.h"

#include <QSqlQuery>
#include <QDebug>

LDbHandle::LDbHandle()
{
}

LDbHandle::~LDbHandle()
{
}

QStringList LDbHandle::getTableNames()
{
    QStringList tableList;
    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QString sql = "SELECT NAME FROM sqlite_master WHERE type = 'table'";
    QSqlQuery query(db);
    if (!query.exec(sql)){
        qDebug()<<"select table name error!";
        return tableList;
    }
    while (query.next()){
        tableList.append(query.value(0).toString());
    }
    Singleton<ConnectionPool>::getInstance().closeConnection(db);

    return tableList;
}

QStringList LDbHandle::getTableFieldNames(const QString &tableName)
{
    QStringList tableList;
    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QString sql = "PRAGMA TABLE_INFO("+tableName+")";
    QSqlQuery query(db);
    if (!query.exec(sql)){
        qDebug()<<"select table fields error!";
        return tableList;
    }

    while (query.next()){
        tableList.append(query.value(1).toString());
    }

    Singleton<ConnectionPool>::getInstance().closeConnection(db);

    return tableList;
}
