#include "KHelper.h"
#include "KHelper_p.h"

#include <QMetaType>

KJsonHelp::KJsonHelp()
    : m_pImpl(new(std::nothrow) KJsonHelpPrivate(this))
{
}

KJsonHelp::~KJsonHelp()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

KJsonHelp *KJsonHelp::instance()
{
    static KJsonHelp _instance;
    return &_instance;
}

QVariant KJsonHelp::getProperty(const char *name) const
{
    return QVariant(name);
}

QVariant KJsonHelp::serializeSubtype(const QMetaProperty &property, const QVariant &value) const
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
        return serializeVariant(property.userType(), value);
    }
}

QVariant KJsonHelp::serializeSubtype(int propertyType, const QVariant &value) const
{
    return serializeVariant(propertyType, value);
}

QVariant KJsonHelp::deserializeSubtype(const QMetaProperty &property, const QJsonValue &value, QObject *parent) const
{
    QVariant v;
    return v;
}

QVariant KJsonHelp::deserializeSubtype(int propertyType, const QJsonValue &value, QObject *parent) const
{
    QVariant v;
    return v;
}

QJsonObject KJsonHelp::getJsonObjFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "open file fail." << file.errorString()
                   << "file:" << filePath;
        return QJsonObject();
    }

    QByteArray baContent = file.readAll();
    file.close();

    return getJsonObj(baContent);
}

bool KJsonHelp::saveJsonObjToFile(const QJsonObject &jsObj, const QString &filePath)
{
    QFile file(filePath);
    QString path = QFileInfo(filePath).absolutePath();
    QDir dir(path);
    if(!dir.exists())
    {
        dir.mkpath(path);
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "open file fail." << file.errorString()
                   << "file:" << filePath;
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << KJsonHelp::jsValue2String(jsObj);

    file.close();

    return true;
}

QJsonObject KJsonHelp::getJsonObj(const QByteArray &jsonData)
{
    QJsonObject jsObj;

    QJsonParseError error;
    QJsonDocument jsDoc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qWarning() << "json parse error." << error.errorString()
                   << " strJson:" << QString(jsonData);
        return jsObj;
    }
    return jsDoc.object();
}

bool KJsonHelp::json2Object(const QJsonObject &jsObj, QObject *object)
{
    if (jsObj.isEmpty() || nullptr == object)
    {
        return false;
    }

    QStringList list;
    const QMetaObject *pMetaObj = object->metaObject();
    for(int i = 0; i < pMetaObj->propertyCount(); i++)
    {
        list << pMetaObj->property(i).name();
    }
    QStringList jsonKeys = jsObj.keys();
    foreach(const QString &proName ,list)
    {
        if(!jsonKeys.contains(proName) || jsObj.value(proName).isNull())
        {
            continue;
        }
        auto v = jsObj.value(proName);
        auto objV = object->property(proName.toLocal8Bit());
        object->setProperty(proName.toLocal8Bit().data(), toVariant(objV.userType(), v));
    }

    return true;
}

QJsonObject KJsonHelp::object2Json(const QObject *object) const
{
    QJsonObject jsObj;
    if(nullptr == object)
    {
        return jsObj;
    }

    const QMetaObject *pMetaObj = object->metaObject();
    for(int i = 0; i < pMetaObj->propertyCount(); i++)
    {
        auto proName = pMetaObj->property(i).name();

        QVariant v = object->property(proName);
        QJsonValue value = fromVariant(v);
        jsObj.insert(proName, value);
    }

    if(jsObj.contains("objectName"))
    {
        jsObj.remove("objectName");
    }

    return jsObj;
}

QByteArray KJsonHelp::jsValue2String(const QJsonValue &jsValue)
{
    QJsonDocument jsDoc;
    if (jsValue.isObject())
    {
        jsDoc.setObject(jsValue.toObject());
    }
    else if (jsValue.isArray())
    {
        jsDoc.setArray(jsValue.toArray());
    }

    return jsDoc.toJson();
}

QJsonValue KJsonHelp::fromVariant(const QVariant &v) const
{
    switch (v.userType())
    {
//    case QMetaType::QRect:      return KHelpUtils::serializeRect(v.toRect()).toJsonValue();
//    case QMetaType::QRectF:     return KHelpUtils::serializeRect(v.toRectF()).toJsonValue();
//    case QMetaType::QPoint:     return QJsonValue(KHelpUtils::formatQPoint(v.toPoint()));
//    case QMetaType::QPointF:    return QJsonValue(KHelpUtils::formatQPoint(v.toPointF()));
//    case QMetaType::QSize:      return QJsonValue(KHelpUtils::formatQSize(v.toSize()));
//    case QMetaType::QSizeF:     return QJsonValue(KHelpUtils::formatQSize(v.toSizeF()));
//    case QMetaType::QLine:      return QJsonValue(KHelpUtils::formatQLine(v.toLine()));
//    case QMetaType::QLineF:     return QJsonValue(KHelpUtils::formatQLine(v.toLineF()));
//    case QMetaType::QPolygon:   return QJsonValue(KHelpUtils::formatQPolygon(v.value<QPolygon>()));
//    case QMetaType::QPolygonF:  return QJsonValue(KHelpUtils::formatQPolygon(v.value<QPolygonF>()));
    default:                    return QJsonValue::fromVariant(v);
    }
}

QVariant KJsonHelp::toVariant(int typeId, const QJsonValue &value)
{
    switch (typeId)
    {
//    case QMetaType::QRect:      return QVariant(KHelpUtils::toQRect<QRect>(value.toArray()));
//    case QMetaType::QRectF:     return QVariant(KHelpUtils::toQRect<QRectF>(value.toArray()));
//    case QMetaType::QPoint:     return QVariant(KHelpUtils::toQPoint<QPoint>(value.toArray()));
//    case QMetaType::QPointF:    return QVariant(KHelpUtils::toQPoint<QPointF>(value.toArray()));
//    case QMetaType::QSize:      return QVariant(KHelpUtils::toQSize<QSize>(value.toArray()));
//    case QMetaType::QSizeF:     return QVariant(KHelpUtils::toQSize<QSizeF>(value.toArray()));
//    case QMetaType::QLine:      return QVariant(KHelpUtils::toQLine<QLine>(value.toArray()));
//    case QMetaType::QLineF:     return QVariant(KHelpUtils::toQLine<QLineF>(value.toArray()));
//    case QMetaType::QPolygon:   return QVariant(KHelpUtils::toQPolygon<QPolygon,QPoint>(value.toArray()));
//    case QMetaType::QPolygonF:  return QVariant(KHelpUtils::toQPolygon<QPolygonF, QPointF>(value.toArray()));
//    case QMetaType::QUuid:      return QVariant(QUuid::fromString(value.toString()));
    default:                    return value;
    }
}

QJsonValue KJsonHelp::serialize(const QVariant &v) const
{
    return serializeVariant(v.userType(), v);
}

QJsonValue KJsonHelp::serializeVariant(int propertyType, const QVariant &v) const
{
    QVariant vValue;
    auto pConverter = m_pImpl->findSerConverter(propertyType);

    qDebug() << "conver:" << pConverter << propertyType << v;
    if(nullptr != pConverter)
    {
        vValue = pConverter->serialize(propertyType, v);
    }
    else
    {
        vValue = v;
    }

    return vValue.toJsonValue();
}
