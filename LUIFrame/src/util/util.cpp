#include "util.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>

Util::Util()
{
    init();
}

Util::~Util()
{
}

bool Util::writeInit(const QString &path, const QString &group,
                     const QString &key,const QVariant &value)
{
    if (path.isEmpty() | key.isEmpty())
        return false;

    //QSettings *set = new QSettings(path,QSettings::IniFormat);
    QSettings set(path,QSettings::IniFormat);
    set.beginGroup(group);
    set.setValue(key,value);
    set.endGroup();

#if 0
    if (set){
        delete set;
        set = NULL;
    }
#endif

    return true;
}

bool Util::readInit(const QString &path,const QString &group,
                    const QString &key,QVariant &value)
{
    if (path.isEmpty() | key.isEmpty())
        return false;

    //QSettings *set = new QSettings(path,QSettings::IniFormat);
    QSettings set(path,QSettings::IniFormat);
    set.beginGroup(group);

    value = set.value(key);
    set.endGroup();
#if 0
    if (set){
        delete set;
        set = NULL;
    }
#endif
    return true;
}

QString Util::getString(const QString &path)
{
    return getConfigValue(path).toString();
}

QStringList Util::getStringList(const QString &path)
{
    return getConfigValue (path).toStringList ();
}

int Util::getInt(const QString &path)
{
    return getConfigValue(path).toInt();
}

bool Util::getBool(const QString &path)
{
    return getConfigValue(path).toBool();
}

void Util::init()
{
//    checkConfigFile("data/config.ini");
//    CreateNewConFile();
}

void Util::CreateNewConFile(const QString &fileInfo)
{
    //写入默认信息
    writeInit(fileInfo,"database","debug",true);
    writeInit(fileInfo,"database","type","QSQLITE");
    writeInit(fileInfo,"database","host","127.0.0.1");
    writeInit(fileInfo,"database","port",3306);
    writeInit(fileInfo,"database","database_name","TOS.db");
    writeInit(fileInfo,"database","username","root");
    writeInit(fileInfo,"database","password","root");
    writeInit(fileInfo,"database","test_on_borrow",true);
    writeInit(fileInfo,"database","test_on_borrow_sql","SELECT 1");
    writeInit(fileInfo,"database","max_wait_time",5000);
    writeInit(fileInfo,"database","max_connection_count",5);

    writeInit(fileInfo,"style","qss_files","style");

    /************网络通信接口**************/
    //是否作为TCP服务器,相反则为客户端
    writeInit(fileInfo,"wifi","tcp_ip","192.168.0.1");
    writeInit(fileInfo,"wifi","tcp_port",8899);
    writeInit (fileInfo,"wifi","r_connect",true);
}

bool Util::checkConfigFile(const QString &fileName)
{
    //这里的判断目前还不完善，因为如果新添加内容时就再无法创建了
    if (fileName.isEmpty())
        return false;

    QFileInfo info(fileName);
    if (!info.exists()){
        CreateNewConFile(fileName);
        return true;
    }
    return false;
}

bool Util::emptyConfigFile(const QString &fileName)
{
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        return file.remove();
    }
    return false;
}

QVariant Util::getConfigValue(const QString &path)
{
    Q_ASSERT(path != "");
    QVariant value;
    QStringList tokens = path.split(".");
    int size = tokens.size();
    if (size != 2)
        return QVariant();

    readInit("data/config.ini",tokens.at(0),tokens.at(1),value);

    return value;
}

