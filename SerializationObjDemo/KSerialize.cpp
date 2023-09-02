
#include "KSerialize.h"
#include "Kserialize_p.h"

KSerialize::KSerialize(QObject *parent)
    : QObject{*new KSerializePrivate{}, parent}
{
    //Q_D(KSerialize);
}

QVariant KSerialize::getProperty(const char *name) const
{
    return property(name);
}

QVariant KSerialize::serializeSubtype(const QMetaProperty &property, const QVariant &value) const
{
    if(property.isEnumType())
    {
        const auto enumMata = property.enumerator();
        QByteArray eName = enumMata.name();
        const auto enumId = QMetaType::type(eName);
        return serializeVariant(enumId, value);
    }
    else
    {
        //qDebug() << "serial subType " << property.name() << " type:" << QMetaType::typeName(property.userType());
        return serializeVariant(property.userType(), value);
    }
}

QVariant KSerialize::serializeSubtype(int propertyType, const QVariant &value) const
{
    return serializeVariant(propertyType, value);
}

QVariant KSerialize::deserializeSubtype(const QMetaProperty &property, const QJsonValue &value, QObject *parent) const
{
    if(property.isEnumType())
    {
        const auto enumMata = property.enumerator();
        QByteArray eName = enumMata.name();
        const auto enumId = QMetaType::type(eName);
        return deserializeVariant(enumId, value, parent, true);
    }
    else
    {
        return deserializeVariant(property.userType(), value, parent);
    }
}

QVariant KSerialize::deserializeSubtype(int propertyType, const QJsonValue &value, QObject *parent) const
{
    return deserializeVariant(propertyType, value, parent);
}

QJsonValue KSerialize::serialize(const QVariant &v) const
{
    return serializeVariant(v.userType(), v);
}

QVariant KSerialize::deserialize(const QJsonValue &json, int metaTypeId, QObject *parent) const
{
    return deserializeVariant(metaTypeId, json, parent);
}

QJsonValue KSerialize::serializeVariant(int propertyType, const QVariant &v) const
{
    Q_D(const KSerialize);
    QVariant vValue;
    try
    {
        if(d->canConvertBasicType(propertyType))
        {
            vValue = d->serializeBasic(propertyType, v);
        }
        else if(d->canConvertGeometty(propertyType))
        {
            vValue = d->serializeGeometry(propertyType, v);
        }
        else if (d->canConvertList(propertyType))
        {
            vValue = d->serializeList(propertyType, v);
        }
        else if (d->canConvertObject(propertyType))
        {
            vValue = d->serializeObject(propertyType, v);
        }
        else
        {
            vValue = d->serializeValue(propertyType, v);
        }
    }
    catch (std::exception &e)
    {
        qWarning() << "exception " << QString(e.what());
    }

    return vValue.toJsonValue();
}

QVariant KSerialize::deserializeVariant(int propertyType, const QJsonValue &value, QObject *parent, bool skipConversion) const
{
    Q_D(const KSerialize);
    Q_UNUSED(parent);
    Q_UNUSED(skipConversion);

    QVariant vValue;
    try
    {
        if(d->canConvertObject(propertyType))
        {
            vValue = d->deserializeObject(propertyType, value);
        }
        else if (d->canConvertBasicType(propertyType))
        {
            vValue = d->deserializeBasic(propertyType, value);
        }
        else if (d->canConvertList(propertyType))
        {
            vValue = d->deserializeList(propertyType, value);
        }
        else
        {
            vValue = d->deserializeValue(propertyType, value);
        }
    }
    catch (std::exception &e)
    {
        qWarning() << "exception " << QString(e.what());
    }

    return vValue;
}

