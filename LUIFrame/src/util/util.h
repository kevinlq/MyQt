#ifndef UTIL_H
#define UTIL_H

class QString;
class QStringList;
class QVariant;

class Util
{
public:
    Util();
    ~Util();

    /**
     * @brief writeInit 写入配置文件
     * @param path  配置文件路径
     * @return void
     */
    static bool writeInit(const QString &path,const QString &group,
                          const QString &key, const QVariant &value);

    /**
     * @brief readInit 读取配置文件
     * @param path  配置文件路径
     * @return void
     */
    static bool readInit(const QString &path, const QString &group,
                         const QString &key, QVariant &value);

    QString getString(const QString &path);

    QStringList getStringList(const QString &path);

    int getInt(const QString &path);

    bool getBool(const QString &path);

    bool checkConfigFile(const QString &fileName);

    bool emptyConfigFile(const QString &fileName);

private:
    /**
     *@brief 初始化默认信息
    */
    void init();

    void CreateNewConFile(const QString &fileInfo);

    /**
     * @brief  : getConfigValue 获取配置信息值
     * @param  : path 配置文件中的属性 group.key
     * @return : variant
     */
    QVariant getConfigValue(const QString &path);

};

#endif // UTIL_H
