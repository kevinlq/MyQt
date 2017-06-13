#include "dbhandle.h"

#include "dbutil.h"


extern "C"{
#include "aisParser/sdk/vdm_parse.h"
}


#define TIMEMS qPrintable (QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME qPrintable (QTime::currentTime().toString("HH:mm:ss"))
#define QDATE qPrintable (QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME qPrintable (QTime::currentTime().toString("HH-mm-ss"))
#define DATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))

#ifdef DB_SQLITE
#define INSERT_SQL  "INSERT INTO "
#else
#define INSERT_SQL  "INSERT IGNORE "
#endif

/***************保存系统中数据表名称*************/
const QString ErrorLog = "`Ais_error_log`";                 //AIS错误信息记录表
const QString AisStatic = "`ais_static`";                   //静态信息表
const QString AisDynamic = "`ais_dynamic`";                 //动态信息表
const QString AisMessage = "`ais_message`";                 //AIS信息表
const QString AisBasestation = "`ais_basestation`";         //AIS基站信息表
const QString AISAidtonavigation = "`ais_aidtonavigation`"; //助航设备表
const QString AisDataLink = "`ais_datalink`";               //数据链路管理
const QString AbnormalInfo = "`abnormal_info`";             //异常信息记录表

DBHandle::DBHandle(QObject *parent)
    : QObject(parent)
{
}

DBHandle::~DBHandle()
{
}

int DBHandle::insertToAisMessage(const qint64 &sourceId,const QByteArray &msg,
                                 const quint8 inputWay)
{
    if (msg.isEmpty()){
        qCritical()<<"msg is empty!";
        return -1;
    }

    QString sql = INSERT_SQL + AisMessage +"(Rev_Datetime,Source_ID,msg,input_id,remark)";
    sql += " VALUES(:revTime,:sourceId,:msg,:inputId,:remark)";
    QVariantMap params;
    params["revTime"]   = STRDATETIMEMS;
    params["sourceId"]  = sourceId;
    params["msg"]       = msg;
    params["inputId"]   = inputWay;
    params["remark"]    = 1;

    return DBUtil::insert(sql,params);
}

int DBHandle::insertToAisDynamicInfo(const qint64 &sourceId, const aismsg_1 *msg1)
{
    QString sql = INSERT_SQL + AisDynamic + "(Rev_Datetime,";
    sql += "Source_ID,Message_ID,RepeatNum,MMSI,Nav_Status,ROT,SOG,Position_Accuracy,";
    sql += "Longitude,Latitude,COG,TrueHeading,UTC_Second,Regional,Spare,RaimFlag, ";
    sql += "SyncState,SlotTimeout,SubMessage)";
    sql += "VALUES(:RvTime,:sourId,:id,:repeaNumt,:mmsi,:nav,:rot,:sog,:pos_ac,:lot,:lat,";
    sql += ":cog,:true_heating,:utc_sec,:regional,:spare,:raim,:syncState,:slotTime,:subMsg)";

    QVariantMap params;
    params["RvTime"]        = STRDATETIMEMS;
    params["sourId"]        = sourceId;
    params["id"]            = msg1->msgid;
    params["repeaNumt"]     = msg1->repeat;
    params["mmsi"]          = store( msg1->userid );
    params["nav"]           = msg1->nav_status;
    params["rot"]           = msg1->rot;
    params["sog"]           = msg1->sog;
    params["pos_ac"]        = msg1->pos_acc;
    params["lot"]           = store( msg1->longitude );
    params["lat"]           = store( msg1->latitude );
    params["cog"]           = msg1->cog;
    params["true_heating"]  = msg1->true_heading;
    params["utc_sec"]       = msg1->utc_sec;
    params["regional"]      = msg1->regional;
    params["spare"]         = msg1->spare;
    params["raim"]          = msg1->raim;
    params["syncState"]     = msg1->sync_state;
    params["slotTime"]      = msg1->slot_timeout;
    params["subMsg"]        = msg1->sub_message;

    return DBUtil::insert(sql,params);
}

int DBHandle::insertToAisDynamicInfo(const qint64 &sourceId,const aismsg_2 *msg2)
{
    QString sql = "";

    sql = INSERT_SQL + AisDynamic + "(Rev_Datetime,Source_ID,Message_ID,";
    sql += "RepeatNum,MMSI,Nav_Status,ROT,SOG,Position_Accuracy,Longitude,Latitude,";
    sql += "COG,TrueHeading,UTC_Second,Regional,Spare,RaimFlag,SyncState,";
    sql += "SlotTimeout,SubMessage)";
    sql += "VALUES(:RvTime,:sourId,:id,:repeaNumt,:mmsi,:nav,:rot,:sog,:pos_ac,:lot,:lat,";
    sql += ":cog,:true_heating,:utc_sec,:regional,:spare,:raim,:syncState,:slotTime,:subMsg)";

    QVariantMap params;
    params["RvTime"]        = STRDATETIMEMS;
    params["sourId"]        = sourceId;
    params["id"]            = msg2->msgid;
    params["repeaNumt"]     = msg2->repeat;
    params["mmsi"]          = store( msg2->userid );
    params["nav"]           = msg2->nav_status;
    params["rot"]           = msg2->rot;
    params["sog"]           = msg2->sog;
    params["pos_ac"]        = msg2->pos_acc;
    params["lot"]           = store( msg2->longitude );
    params["lat"]           = store( msg2->latitude );
    params["cog"]           = msg2->cog;
    params["true_heating"]  = msg2->true_heading;
    params["utc_sec"]       = msg2->utc_sec;
    params["regional"]      = msg2->regional;
    params["spare"]         = msg2->spare;
    params["raim"]          = msg2->raim;
    params["syncState"]     = msg2->sync_state;
    params["slotTime"]      = msg2->slot_timeout;
    params["subMsg"]        = msg2->sub_message;

    return DBUtil::insert(sql,params);
}

int DBHandle::insertToAisDynamicInfo(const qint64 &sourceId, const aismsg_3 *msg3)
{
    QString sql = "";

    sql = INSERT_SQL + AisDynamic + "(Rev_Datetime,Source_ID,Message_ID,";
    sql += "RepeatNum,MMSI,Nav_Status,ROT,SOG,Position_Accuracy,Longitude,";
    sql += "Latitude,COG,TrueHeading,UTC_Second,Regional,Spare,RaimFlag, ";
    sql += "SyncState,SlotTimeout,SubMessage)";
    sql += "VALUES(:RvTime,:sourId,:id,:repeaNumt,:mmsi,:nav,:rot,:sog,:pos_ac,:lot,:lat,";
    sql += ":cog,:true_heating,:utc_sec,:regional,:spare,:raim,:syncState,:slotTime,:subMsg)";

    QVariantMap params;
    params["RvTime"]        = STRDATETIMEMS;
    params["sourId"]        = sourceId;
    params["id"]            = msg3->msgid;
    params["repeaNumt"]     = msg3->repeat;
    params["mmsi"]          = store( msg3->userid );
    params["nav"]           = msg3->nav_status;
    params["rot"]           = msg3->rot;
    params["sog"]           = msg3->sog;
    params["pos_ac"]        = msg3->pos_acc;
    params["lot"]           = store( msg3->longitude );
    params["lat"]           = store( msg3->latitude );
    params["cog"]           = msg3->cog;
    params["true_heating"]  = msg3->true_heading;
    params["utc_sec"]       = msg3->utc_sec;
    params["regional"]      = msg3->regional;
    params["spare"]         = msg3->spare;
    params["raim"]          = msg3->raim;
    params["syncState"]     = msg3->sync_state;
    params["slotTime"]      = msg3->slot_increment;
    params["subMsg"]        = msg3->num_slots;


    return DBUtil::insert(sql,params);
}

int DBHandle::insertBaseStationInfo(const qint64 &sourceId, const aismsg_4 *msg4)
{
    QString sql;
    QVariantMap params;

    /**
      2017年5月31日17:29:29
      对同一个基站数据只存一份，下次报文来只更新时间戳
    */
    sql = "SELECT MMSI FROM "+ AisBasestation +" WHERE MMSI = :mmsi";
    params["mmsi"]  = store (msg4->userid);
    if (DBUtil::selectInt64(sql,params) > 0)
    {
        //该基站记录基站信息已经存在，直接更新时间戳
        sql = "UPDATE " + AisBasestation + " SET Rev_Datetime = :rTime,UTC_Year=:year,";
        sql += "UTC_Month=:month,UTC_Day=:day,UTC_Hour=:hour,UTC_Minute=:minute,";
        sql += "UTC_Second=:second WHERE MMSI=:mmsi";
        params.clear();
        params["rTime"] = STRDATETIMEMS;
        params["year"]  = msg4->utc_year;
        params["month"] = msg4->utc_month;
        params["day"]   = msg4->utc_day;
        params["hour"]  = msg4->utc_hour;
        params["minute"]= msg4->utc_minute;
        params["second"] = msg4->utc_second;
        params["mmsi"]  = store( msg4->userid);
    }else{
        //直接插入新的基站信息
        sql = INSERT_SQL + AisBasestation + "(Rev_Datetime,Source_ID,Message_ID,RepeatNum,MMSI,";
        sql += "UTC_Year,UTC_Month,UTC_Day,UTC_Hour,UTC_Minute,UTC_Second,Position_Accuracy,";
        sql += "Longitude,Latitude,Fixing_Device,Spare,Raim,SyncState,SlotTimeOut,SubMessage) ";

        sql += "VALUES(:reTime,:sourId,:msgId,:repeat,:mmsi,:utcYear,:utcMonth,:utcDay,";
        sql += ":utcHour,:utcMinute,:utcSecond,:posAcc,:lot,:lat,:fixDev,:spare,:raim,";
        sql += ":syncState,:slotTimeOut,:subMsg)";

        params.clear();
        params["reTime"]        = STRDATETIMEMS;
        params["sourId"]        = sourceId;
        params["msgId"]         = msg4->msgid;
        params["repeat"]        = msg4->repeat;
        params["mmsi"]          = store( msg4->userid);
        params["utcYear"]       = msg4->utc_year;
        params["utcMonth"]      = msg4->utc_month;
        params["utcDay"]        = msg4->utc_day;
        params["utcHour"]       = msg4->utc_hour;
        params["utcMinute"]     = msg4->utc_minute;
        params["utcSecond"]     = msg4->utc_second;
        params["posAcc"]        = msg4->pos_acc;
        params["lot"]           = store( msg4->longitude);
        params["lat"]           = store(msg4->latitude);
        params["fixDev"]        = msg4->pos_type;
        params["spare"]         = msg4->spare;
        params["raim"]          = msg4->raim;
        params["syncState"]     = msg4->sync_state;
        params["slotTimeOut"]   = msg4->slot_timeout;
        params["subMsg"]        = msg4->sub_message;
    }

    return DBUtil::insert(sql,params);
}

int DBHandle::insertToAisDynamicB(const quint64 &sourceId, const aismsg_18 *msg18)
{
    QString sql = INSERT_SQL + AisDynamic + "(Rev_Datetime,Source_ID,Message_ID,RepeatNum,";
    sql += "MMSI,SOG,Position_Accuracy,Longitude,Latitude,COG,TrueHeading,UTC_Second,";
    sql += "RaimFlag,SyncState,SlotTimeout,SubMessage) ";
    sql += "VALUES(:rvTime,:sourId,:msgId,:repeat,:mmsi,:sog,:pos_ac,:lot,:lat,:cog,";
    sql += ":true_heating,:utc_sec,:raim,:syncState,:slotTime,:subMsg)";

    QVariantMap params;
    params["rvTime"]        = STRDATETIMEMS;
    params["sourId"]        = sourceId;
    params["msgId"]         = msg18->msgid;
    params["repeat"]        = msg18->repeat;
    params["mmsi"]          = store( msg18->userid);
    params["sog"]           = msg18->sog;
    params["pos_ac"]        = msg18->pos_acc;
    params["lot"]           = store( msg18->longitude);
    params["lat"]           = store( msg18->latitude);
    params["cog"]           = msg18->cog;
    params["true_heating"]  = msg18->true_heading;
    params["utc_sec"]       = msg18->utc_sec;
    params["raim"]          = msg18->raim;
    params["syncState"]     = msg18->sotdma.sync_state;
    params["slotTime"]      = msg18->sotdma.slot_timeout;
    params["subMsg"]        = msg18->sotdma.sub_message;

    return DBUtil::insert (sql,params);
}

int DBHandle::insertToAisDynamicBEx(const quint64 &sourceId, const aismsg_19 *msg19)
{
    QString sql;
    sql = INSERT_SQL + AisDynamic + "(Rev_Datetime,Source_ID,Message_ID,RepeatNum,MMSI,SOG,";
    sql += "Position_Accuracy,Longitude,Latitude,COG,TrueHeading,";
    sql += "UTC_Second,RaimFlag) ";
    sql += "VALUES(:rvTime,:sourId,:msgId,:repeat,:mmsi,:sog,:pos_ac,:lot,:lat,:cog,";
    sql += ":true_heating,:utc_sec,:raim)";

    QVariantMap params;
    params["rvTime"]        = STRDATETIMEMS;
    params["sourId"]        = sourceId;
    params["msgId"]         = msg19->msgid;
    params["repeat"]        = msg19->repeat;
    params["mmsi"]          = store( msg19->userid);
    params["sog"]           = msg19->sog;
    params["pos_ac"]        = msg19->pos_acc;
    params["lot"]           = store (msg19->longitude);
    params["lat"]           = store( msg19->latitude);
    params["cog"]           = msg19->cog;
    params["true_heating"]  = msg19->true_heading;
    params["utc_sec"]       = msg19->utc_sec;
    params["raim"]          = msg19->raim;

    return DBUtil::insert(sql,params);
}

int DBHandle::insertToAisDataLink(const quint64 &sourceId, const aismsg_20 *msg20)
{
    QString sql = "";
    sql = INSERT_SQL + AisDataLink +"(Rev_Datetime,Source_ID,Message_ID,";
    sql += "Repeat_Indication,MMSI)";
    sql += " VALUES(:rTime,:sourceId,:msgId,:repeat,:mmsi)";

    QVariantMap params;
    params["rTime"]     = STRDATETIMEMS;
    params["sourceId"]  = sourceId;
    params["msgId"]     = msg20->msgid;
    params["repeat"]    = msg20->repeat;
    params["mmsi"]      = store( msg20->userid );

    return DBUtil::insert(sql,params);
}

int DBHandle::insertAISStaticB(const qint64 &sourceId, const aismsg_24 *msg24)
{
    QString sql = "";
    QVariantMap params;

    //首先必须判断对应MMSI是否存在，如存在则直接更新，不存在则创建
    sql = "SELECT MMSI FROM " + AisStatic +" WHERE MMSI = :mmsi";
    params["mmsi"] = store( msg24->userid);
    if ( DBUtil::selectInt64(sql,params) > 0){
        //存在该条信息，直接更新即可
#if DEBUG_OUT
        qDebug()<<"ship mmsi exist! start update!\n";
#endif
        if (0 == msg24->part_number){
            sql = "UPDATE " + AisStatic + " SET Rev_Datetime=:rTime,Ship_Name=:name,";
            sql += "PartAB=:part WHERE MMSI=:mmsi";
            params.clear();
            params["rTime"] = STRDATETIMEMS;
            params["name"]  = msg24->name;
            params["part"]  = msg24->part_number;
            params["mmsi"]  = store( msg24->userid);
        }else{
            sql = "UPDATE " + AisStatic + " SET Rev_Datetime=:rTime,Call_Sign=:callsing,";
            sql += "Ship_Type=:shipType,To_Bow=:toBow,To_Stern=:toStern,To_Port=:toPort,";
            sql += "To_StarBoard=:toStarBoard WHERE MMSI =:mmsi";

            params.clear();
            params["callsing"]      = msg24->callsign;
            params["shipType"]      = msg24->ship_type;
            params["toBow"]         = msg24->dim_bow;
            params["toStern"]       = msg24->dim_stern;
            params["toPort"]        = msg24->dim_port;
            params["toStarBoard"]   = msg24->dim_starboard;
            params["mmsi"]          = store( msg24->userid);
        }
    }else{
#if DEBUG_OUT
        qDebug()<<"ship mmsi not exist start insert\r\n";
#endif
        //不存在则直接插入
        if (0 == msg24->part_number)
        {
            sql = INSERT_SQL + AisStatic + "(Rev_Datetime,Source_ID,Message_ID,";
            sql += "Repeat_Indication,MMSI,Ship_Name,PartAB,Spare) ";
            sql += "VALUES(:revTime,:sourceId,:msgId,:repeat,:mmsi,:name,:part,:spare)";

            params.clear();
            params["revTime"]   = STRDATETIMEMS;
            params["sourceId"]  = sourceId;
            params["msgId"]     = 24;
            params["repeat"]    = msg24->repeat;
            params["mmsi"]      = store (msg24->userid);
            params["name"]      = msg24->name;
            params["part"]      = msg24->part_number;
            params["spare"]     = msg24->spare;

        }else if ( 1 == msg24->part_number)
        {
            //B part
            sql = INSERT_SQL + AisStatic + "(Rev_Datetime,Source_ID,Message_ID,";
            sql += "Repeat_Indication,MMSI,Call_Sign,Ship_Type,To_Bow,To_Stern,To_Port, ";
            sql += "To_StarBoard,PartAB,Spare) ";
            sql += "VALUES(:revTime,:sourceId,:msgId,:repeat,:mmsi,:callSing,:shipType,";
            sql += ":toBow,:toStern,:toPort,:toStarBoard,:part,:spare)";

            params.clear();
            params["revTime"]       = STRDATETIMEMS;
            params["sourceId"]      = sourceId;
            params["msgId"]         = 24;
            params["repeat"]        = msg24->repeat;
            params["mmsi"]          = store (msg24->userid);
            params["callSing"]      = msg24->callsign;
            params["shipType"]      = msg24->ship_type;
            params["toBow"]         = msg24->dim_bow;
            params["toStern"]       = msg24->dim_stern;
            params["toPort"]        = msg24->dim_port;
            params["toStarBoard"]   = msg24->dim_starboard;
            params["part"]          = msg24->part_number;
            params["spare"]         = msg24->spare;
        }
    }
    return DBUtil::insert(sql,params);
}

int DBHandle::insertAISErrorInfo(const int &msgId,
                                 const QByteArray &msg,
                                 const QString &reason)
{
    QString sql;
    sql = INSERT_SQL + ErrorLog + "(Rev_Datetime,Message_ID,Raw_Message,Error_Info) ";
    sql += "VALUES (:reTime,:msgId,:rawMsg,:errorInfo)";

    QVariantMap params;
    params["reTime"]    = STRDATETIMEMS;
    params["msgId"]     = msgId;
    params["rawMsg"]    = msg;
    params["errorInfo"] = reason;

    return DBUtil::insert(sql,params);

}

qint64 DBHandle::getMaxSourceId()
{
    QString sql = "SELECT MAX(Source_ID) FROM "+AisMessage;

    return DBUtil::selectInt64(sql);
}

QStringList DBHandle::getStrings(const QString &startTime, const QString &endTime)
{
    QString sql = "SELECT ais_static.MMSI,IMO_Number,TrueHeading,Call_Sign,SOG,Ship_Name,";
    sql += "Ship_Type,Nav_Status,ETA,Destination,ais_dynamic.Longitude,ais_dynamic.Latitude";
    sql += " FROM ais_static,ais_dynamic";
    sql += " WHERE ais_static.Rev_Datetime >= :sT AND ais_static.Rev_Datetime:eT";
    QVariantMap params;
    params["sT"] = startTime;
    params["eT"] = endTime;

    return DBUtil::selectStrings(sql,params);
}

int DBHandle::insertAbnormalInfo(const long mmsi, const quint8 id,
                                 const QString &abnormalDetail,
                                 const QString &remark)
{
    QString sql;
    sql = "INSERT INTO " + AbnormalInfo + "(record_date,MMSI,abnormal_id,abnormal_detail,";
    sql += "remark)";
    sql += "VALUES(:rTime,:mmsi,:id,:detail,:remark)";

    QVariantMap params;
    params["rTime"]     = STRDATETIMEMS;
    params["mmsi"]      = store( mmsi);
    params["id"]        = id;
    params["detail"]    = abnormalDetail;
    params["remark"]    = remark;

    return DBUtil::insert(sql,params);
}

bool DBHandle::emptyTable(const QString &sql)
{
    return DBUtil::empty(sql);
}

QVariant DBHandle::store(unsigned long input)
{
    unsigned long long data = (unsigned long long) input;
    QVariant qvariant(data);
    return qvariant;
}
