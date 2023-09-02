
#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QVariant>

#include "KSerializationHelper.h"

class KSerializePrivate;
class KSerialize : public QObject , public SerializationHelper
{
    Q_OBJECT
public:
    explicit KSerialize(QObject *parent = nullptr);
protected:
    QVariant getProperty(const char *name) const override;
    QVariant serializeSubtype(const QMetaProperty &property, const QVariant &value) const override;
    QVariant serializeSubtype(int propertyType, const QVariant &value) const override;

    QVariant deserializeSubtype(const QMetaProperty &property, const QJsonValue &value, QObject *parent) const override;
    QVariant deserializeSubtype(int propertyType, const QJsonValue &value, QObject *parent) const override;

public:
    // serialize a QVariant to a QJsonValue
    QJsonValue serialize(const QVariant &v) const;
    QVariant deserialize(const QJsonValue &json, int metaTypeId, QObject *parent = nullptr) const;

    template <typename T>
    struct variant_helper {
        static inline QVariant toVariant(const T &data) {
            return QVariant::fromValue<T>(data);
        }
        static inline T fromVariant(const QVariant &data) {
            return data.template value<T>();
        }
    };

    template <typename T>
    QJsonValue serialize(const T &data) const;

    template <typename T>
    T deserialize(const QJsonValue &json, QObject *parent = nullptr) const;

private:
    QJsonValue serializeVariant(int propertyType, const QVariant &v) const;
    QVariant deserializeVariant(int propertyType, const QJsonValue &value, QObject *parent, bool skipConversion = false) const;

private:
    Q_DECLARE_PRIVATE(KSerialize)
};

template<typename T>
QJsonValue KSerialize::serialize(const T &data) const
{
    return serialize(QVariant::fromValue(data));
}

template<typename T>
T KSerialize::deserialize(const QJsonValue &json, QObject *parent) const
{
    return variant_helper<T>::fromVariant(deserialize(json, qMetaTypeId<T>() ,parent));
}

