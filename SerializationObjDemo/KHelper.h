/****************************************************************************
**
Copyright (C) 2023 kevinlq <kevinlq0912@gmail.com>.
** Contact: http://kevinlq.com
公众号：devstone
**
** This file is part of KAutoTools
**
****************************************************************************/

#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>
#include "KSerializationHelper.h"

class KJsonHelpPrivate;

// JSON 辅助类
class KJsonHelp : public SerializationHelper
{
    KJsonHelp();
public:
    ~KJsonHelp();
    static KJsonHelp * instance();

    QVariant getProperty(const char *name) const override;
    QVariant serializeSubtype(const QMetaProperty &property, const QVariant &value) const override;
    QVariant serializeSubtype(int propertyType, const QVariant &value) const override;
    QVariant deserializeSubtype(const QMetaProperty &property, const QJsonValue &value, QObject *parent) const override;
    QVariant deserializeSubtype(int propertyType, const QJsonValue &value, QObject *parent) const override;

    QJsonObject getJsonObjFromFile(const QString &filePath);
    bool        saveJsonObjToFile(const QJsonObject &jsObj, const QString &filePath);

    QJsonObject getJsonObj(const QByteArray &jsonData);

    bool json2Object(const QJsonObject &jsObj, QObject *object);
    QJsonObject object2Json(const QObject *object) const;

    QByteArray jsValue2String(const QJsonValue &jsValue);

    QJsonValue fromVariant(const QVariant &variant) const;
    QVariant   toVariant(int typeId, const QJsonValue &value);

    // serialize a QVariant to a QJsonValue
    QJsonValue serialize(const QVariant &v) const;

    template <typename T>
    QJsonValue serialize(const T &data) const;


private:
    QJsonValue serializeVariant(int propertyType, const QVariant &v) const;

private:
    KJsonHelpPrivate *m_pImpl = nullptr;
};

template<typename T>
QJsonValue KJsonHelp::serialize(const T &data) const
{
    return serialize(QVariant::fromValue(data));
}
