/****************************************************************************
**
** Date    		: 2017-04-13
** Author  		: KevinLi
** E-Mail  		: kevinlq0912@163.com
** QQ      		: 2313828706
** Version 		: V1.0
** Description	: 这里封装了对数据库的一些操作
** If you have any questions , please contact me
** http://blog.csdn.net/u013704336
** https://github.com/kevinlq
** https://git.oschina.net/kevinlq0912
** git@git.oschina.net:kevinlq0912/AIOMachineSystem.git
**
****************************************************************************/
#include "dbutil.h"

#include "ConnectionPool.h"
#include "util/config.h"

DBUtil::DBUtil()
{
}

int DBUtil::insert(const QString &sql, const QVariantMap &params)
{
    int id = -1;

    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QSqlQuery query(db);
    query.prepare(sql);
    bingValues(&query,params);
    if (query.exec ()){
        id = query.lastInsertId ().toInt ();// 插入行的主键
    }
    debug(query,params);
    Singleton<ConnectionPool>::getInstance().closeConnection(db);

    return id;
}

bool DBUtil::update(const QString &sql, const QVariantMap &params)
{
    bool result;
    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QSqlQuery query(db);
    query.prepare(sql);
    bingValues(&query,params);
    if (query.exec ()){
        if (query.exec ()){
            result = query.lastError ().type () == QSqlError::NoError;
        }else
            result = false;
    }else
        result = false;

    debug(query,params);
    Singleton<ConnectionPool>::getInstance().closeConnection(db);

    return result;
}

bool DBUtil::empty(const QString &sql, const QVariantMap &params)
{
    bool result;
    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QSqlQuery query(db);
    query.prepare(sql);
    bingValues(&query,params);
    if (query.exec ()){
        result = query.lastError ().type ()== QSqlError::NoError;
    }else
        result = false;

    debug(query,params);
    Singleton<ConnectionPool>::getInstance().closeConnection(db);

    return result;
}

int DBUtil::selectInt(const QString &sql, const QVariantMap &params)
{
    return selectVariant (sql,params).toInt ();
}

qint64 DBUtil::selectInt64(const QString &sql, const QVariantMap &params)
{
    return selectVariant (sql,params).toLongLong ();
}

QString DBUtil::selectString(const QString &sql, const QVariantMap &params)
{
    return selectVariant (sql,params).toString ();
}

QStringList DBUtil::selectStrings(const QString &sql, const QVariantMap &params)
{
    QStringList strings;
    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QSqlQuery query(db);
    query.prepare(sql);
    bingValues(&query,params);
    if (query.exec ()){
        while (query.next ()){
            strings.append (query.value (0).toString ());
        }
    }
    debug(query,params);
    Singleton<ConnectionPool>::getInstance().closeConnection(db);
    return strings;
}

QDate DBUtil::DBUtil::selectDate(const QString &sql, const QVariantMap &params)
{
    return selectVariant (sql,params).toDate ();
}

QDateTime DBUtil::selectDateTime(const QString &sql, const QVariantMap &params)
{
    return selectVariant (sql,params).toDateTime ();
}

QVariant DBUtil::selectVariant (const QString &sql, const QVariantMap &params)
{
    QVariant result;
    QSqlDatabase db = Singleton<ConnectionPool>::getInstance().openConnection();
    QSqlQuery query(db);

    query.prepare(sql);
    bingValues(&query,params);
    if (query.exec ()){
        if (query.next ()){
            result = query.value (0);
        }
    }
    debug(query,params);
    Singleton<ConnectionPool>::getInstance().closeConnection(db);
    return result;
}

void DBUtil::bingValues(QSqlQuery *query, const QVariantMap &params)
{
    for (QVariantMap::const_iterator i = params.constBegin();
         i != params.constEnd();i++){
        query->bindValue(":" + i.key(),i.value());
    }
}

void DBUtil::debug(const QSqlQuery &query, const QVariantMap &params)
{
    if ( Singleton<Config>::getInstance().isDatabaseDebug())
    {
        if (query.lastError().type() != QSqlError::NoError)
        {
            qDebug()<<"=> SQL Error:"<<query.lastError().text().trimmed();
        }
        qDebug()<<"=> SQL Query"<<query.lastQuery();

        if (params.size() > 0)
        {
            qDebug()<<"=> SQL Params:"<<params;
        }
    }
}
