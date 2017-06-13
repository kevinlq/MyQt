#ifndef CONFIG_H
#define CONFIG_H

#include "util/Singleton.h"

#include <QVariant>

class QString;
class QStringList;
class Util;

class Config
{
    SINGLETON(Config)

    public:

    //设置应用程序路径
    void setAppPath(const QString &path);

    //创建默认配置信息到配置文件
    bool loadDefaultInfo();

    //清空文件信息
    bool emptyConfigFile();

    //写入配置文件
    bool writeInitfile(const QString &group,const QString &key,
                       const QVariant &value);

    bool writeInitfile(const QString &group,const QVariantMap &params);

    // 数据库信息
    void destroy();
    QString getAppPath()const;
    QString getDatabaseType() const;            // 数据库的类型, 如QPSQL, QSQLITE, QMYSQL
    QString getDatabaseHost() const;            // 数据库主机的IP
    QString getDatabaseName() const;            // 数据库名
    QString getDatabaseUsername() const;        // 登录数据库的用户名
    QString getDatabasePassword() const;        // 登录数据库的密码
    QString getDatabaseTestOnBorrowSql() const; // 验证连接的 SQL
    bool getDatabaseTestOnBorrow() const;       // 是否验证连接
    int  getDatabaseMaxWaitTime() const;        // 线程获取连接最大等待时间
    int  getDatabaseMaxConnectionCount() const; // 最大连接数
    int  getDatabasePort() const;               // 数据库的端口号
    bool isDatabaseDebug() const;               // 是否打印出执行的 SQL 语句和参数

    // 其它
    QString getWifiServerIp() const;            //获取wifiIP地址
    int getWifiServerPort() const;              //获取wifi端口号
    bool isRconnect() const;                    //是否自动重连


public:
    void conTest();

private:
    Util    *m_pUtil;
};

#endif // CONFIG_H
