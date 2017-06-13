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
#ifndef DBUTIL_H
#define DBUTIL_H

#include <QMap>
#include <QList>
#include <QtSql>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>
#include <functional>

using namespace std;

typedef void( *queryCall)(QSqlQuery *query);

class QString;

class DBUtil
{
public:
    DBUtil();

    /**
     * 执行插入语句，并返回插入行的 id.
     * @param sql
     * @param params
     * @return 如果执行成功返插入的记录的 id，否则返回 -1.
     */
    static int insert(const QString &sql,
                      const QVariantMap &params = QVariantMap());

    /**
     * 执行更新语句 (update 和 delete 语句都是更新语句).
     * @param sql
     * @param params
     * @return 如没有错误返回 true， 有错误返回 false.
     */
    static bool update(const QString &sql, const QVariantMap &params = QVariantMap());

    /**
      @brief 清空某个表操作
      @param sql 执行sql语句
    */
    static bool empty(const QString &sql,const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个整数值，如查询记录的个数，和等.
     * @param result
     * @param sql
     * @param params
     * @return 返回 int
     */
    static int selectInt(const QString &sql,
                         const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个长整数值, 如果返回的是时间戳时很方便.
     * @param result
     * @param sql
     * @param params
     * @return 返回长整数
     */
    static qint64 selectInt64(const QString &sql,
                              const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个字符串.
     * @param str
     * @param sql
     * @param params
     * @return 返回字符串
     */
    static QString selectString(const QString &sql,
                                const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是多个字符串.
     * @param strs
     * @param sql
     * @param params
     * @return 返回 string list.
     */
    static QStringList selectStrings(const QString &sql,
                                     const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个日期类型.
     * @param date
     * @param sql
     * @param params
     * @return 返回 date
     */
    static QDate selectDate(const QString &sql,
                             const QVariantMap &params= QVariantMap());

    /**
     * 查询结果是一个日期时间类型.
     * @param date
     * @param sql
     * @param params
     * @return 返回 date time
     */
    static QDateTime selectDateTime(const QString &sql,
                                    const QVariantMap &params = QVariantMap());

    /**
     * 查询结果是一个 QVariant.
     * @param str
     * @param sql
     * @param params
     * @return 返回 variant
     */
    static QVariant selectVariant(const QString &sql,
                                  const QVariantMap &params = QVariantMap());

private:

    static void bingValues(QSqlQuery *query,const QVariantMap &params);


    static void debug(const QSqlQuery &query, const QVariantMap &params);
};

#endif // DBUTIL_H
