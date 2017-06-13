#ifndef DBHANDLE_H
#define DBHANDLE_H

#include <QObject>
#include <QStringList>

struct aismsg_1;
struct aismsg_2;
struct aismsg_3;
struct aismsg_4;
struct aismsg_5;
struct aismsg_18;
struct aismsg_19;
struct aismsg_20;
struct aismsg_21;
struct aismsg_24;

class DBHandle : public QObject
{
    enum IntegrityOpt{
        IntegrityAdd = 0,
        IntegrityModify = 1,
        IntegrityDelete = 2
    };
    Q_OBJECT
public:
    explicit DBHandle(QObject *parent = 0);
    ~DBHandle();

public Q_SLOTS:

    /**
     * @brief:   insertToAisMessage 保存AIS原始数据
     * @param:   sourceId AIS消息源
     * @param:   msg 原始报文
     * @param:   inputway 数据接入方式
     */
    static int insertToAisMessage(const qint64 &sourceId,
                                  const QByteArray &msg,
                                  const quint8 inputWay);

    /**
     * @brief:  insertToAisDynamicInfo 插入1号类型AIS(位置报告)
     * @param:  sourceId 编号ID
     * @param:  msg1 AIS 1号消息指针
     * @return: 数据保存是否成功 成功返回TRUE,失败返回FALSE
    */
    static int insertToAisDynamicInfo(const qint64 &sourceId,
                                      const aismsg_1 *msg1);

    static int insertToAisDynamicInfo(const qint64 &sourceId,
                                      const aismsg_2 *msg2);

    static int insertToAisDynamicInfo(const qint64 &sourceId,
                                      const aismsg_3 *msg3);

    /**
     *AIS Message 4 - Base Station Save
    */
    static int insertBaseStationInfo(const qint64 &sourceId,
                                     const aismsg_4 *msg4);

    /**
      *AIS Message 18 -- Dynamic save
     */
    static int insertToAisDynamicB(const quint64 &sourceId,
                                   const aismsg_18 *msg18);

    /**
      *AIS Message 19  --Dynamic save  extend
     */
    static int insertToAisDynamicBEx(const quint64 &sourceId,
                                     const aismsg_19 *msg19);

    /**
     * AIS Message 20 --Data Link Manage
    **/
    static int insertToAisDataLink(const quint64 &sourceId,
                                   const aismsg_20 *msg20);


    /**
     *AIS Message 24 -- static save
    */
    static int insertAISStaticB(const qint64 &sourceId,
                                const aismsg_24 *msg24);

    /**
      * @brief:  插入AIS解析过程中发生的错误信息
      * @param:  msgId-ais消息类型编号
      *          msg:原始ais消息
      *          reason:出现错误的原因
      * @return  插入的行数
     */
    static int insertAISErrorInfo(const int &msgId,
                                  const QByteArray &msg,
                                  const QString &reason);

    /**
     * @brief:   getMaxSourceId 获取数据源最大编号
     * @return:  最大编号+1
     */
    static qint64 getMaxSourceId();

    /**
     * @brief getStrings 获取当天时间段内的船只信息
     * @param time 当前时间
     * @return QStringList
     */
    static QStringList getStrings(const QString &startTime,const QString &endTime);

    /**
     * @brief insertAbnormalInfo 异常信息保存
     * @param mmsi:  船只MMSI
     * @param id:    异常编号，由具体异常信息指定
     * @param detail:异常明细
     * @param remark:备注
     * @return void
     */
    static int insertAbnormalInfo(const long mmsi,const quint8 id,
                                  const QString &abnormalDetail,
                                  const QString &remark = QString());

    static bool emptyTable(const QString &sql);

private:
    static QVariant store (unsigned long int input);

};

#endif // DBHANDLE_H
