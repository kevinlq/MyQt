#include "KHelper_p.h"


Exception::Exception(const QByteArray &what)
    : m_what(what)
{
}
const char *Exception::what() const noexcept
{
    return m_what.constData();
}
void Exception::raise() const
{
    throw *this;
}
Exception *Exception::clone() const
{
    auto exc = new Exception(QByteArray());
    return exc;
}


bool QObjectConverter::canConvert(int metaTypeId) const
{
    auto flags = QMetaType(metaTypeId).flags();
    return flags.testFlag(QMetaType::PointerToQObject);
}

QVariant QObjectConverter::serialize(int propertyType, const QVariant &value) const
{
    QVariantMap rValue;
    auto object = value.value<QObject*>();
    if (!object)
    {
        qWarning() << "error. " << object;
        return rValue;
    }

    const QMetaObject *metaObject = object->metaObject();
    if(nullptr == metaObject)
    {
        throw Exception(QByteArray("Unable to get metaobject for type ") + QMetaType::typeName(propertyType));
    }

    auto i = QObject::staticMetaObject.indexOfProperty("objectName");
    for(; i < metaObject->propertyCount(); i++)
    {
        auto property = metaObject->property(i);
        {
           rValue[QString::fromUtf8(property.name())] = helper()->serializeSubtype(property, property.read(object));
        }
    }
    return rValue;
}

QVariant QObjectConverter::deserialize(int propertyType, const QVariant &value) const
{
    QVariant rValue;
    auto object = value.value<QObject*>();
    if (!object)
    {
        return rValue;
    }

    const QMetaObject *metaObject = object->metaObject();
    if(nullptr == metaObject)
    {
        throw Exception(QByteArray("Unable to get metaobject for type ") + QMetaType::typeName(propertyType));
    }
    return rValue;
}


bool GeometryConverter::canConvert(int metaTypeId) const
{
    static const QVector<int> types {
        QMetaType::QSize,   QMetaType::QSizeF,
        QMetaType::QPoint,  QMetaType::QPointF,
        QMetaType::QLine,   QMetaType::QLineF,
        QMetaType::QRect,   QMetaType::QRectF,
    };
    return types.contains(metaTypeId);
}

QVariant GeometryConverter::serialize(int propertyType, const QVariant &value) const
{
    switch (propertyType)
    {
    case QMetaType::QSize:      return KHelpUtils::serializeSize(value.toSize());
    case QMetaType::QSizeF:     return KHelpUtils::serializeSize(value.toSizeF());
    case QMetaType::QPoint:     return KHelpUtils::serializePoint(value.toPoint());
    case QMetaType::QPointF:    return KHelpUtils::serializePoint(value.toPointF());
    case QMetaType::QLine:      return KHelpUtils::serializeLine(value.toLine());
    case QMetaType::QLineF:     return KHelpUtils::serializeLine(value.toLineF());
    case QMetaType::QRect:      return KHelpUtils::serializeRect(value.toRect());
    case QMetaType::QRectF:     return KHelpUtils::serializeRect(value.toRectF());
    default:                    throw Exception{"Invalid type id"};
    }
}

QVariant GeometryConverter::deserialize(int propertyType, const QVariant &value) const
{
    const auto array = value.toJsonArray();
    switch (propertyType)
    {
    case QMetaType::QSize:      return KHelpUtils::deserializeSize<QSize>(array);
    case QMetaType::QSizeF:     return KHelpUtils::deserializeSize<QSizeF>(array);
    case QMetaType::QPoint:     return KHelpUtils::deserializePoint<QPoint>(array);
    case QMetaType::QPointF:    return KHelpUtils::deserializePoint<QPointF>(array);
    case QMetaType::QLine:      return KHelpUtils::deserializeLine<QLine>(array);
    case QMetaType::QLineF:     return KHelpUtils::deserializeLine<QLineF>(array);
    case QMetaType::QRect:      return KHelpUtils::deserializeRect<QRect>(array);
    case QMetaType::QRectF:     return KHelpUtils::deserializeRect<QRectF>(array);
    default:                    throw Exception{"Invalid type id"};
    }
}


QReadWriteLock KJsonHelpPrivate::m_typeConverterFactoryLock;
QList<TypeConverterFactory*> KJsonHelpPrivate::m_typeConverterFactories
    {
     new TypeConverterStandardFactory<GeometryConverter>{},
     new TypeConverterStandardFactory<QObjectConverter>{},
     };
KJsonHelpPrivate::KJsonHelpPrivate(SerializationHelper *parent)
    : m_q(parent)
{
}

KJsonHelpPrivate::~KJsonHelpPrivate()
{
}

QSharedPointer<TypeConverter> KJsonHelpPrivate::findSerConverter(int propertyType) const
{
    updateConverterStore();

    auto converter = m_serCache.get(propertyType);
    if(nullptr != converter)
    {
        return converter;
    }

    QReadLocker cLocker{&m_typeConverters.lock};
    for (const auto &converter : qAsConst(m_typeConverters.store))
    {
        if (converter && converter->canConvert(propertyType))
        {
//            qCWarning(logSerializer) << "Found and cached serialization converter" << converter->name()
//                                     << "for type:" <<  QMetaTypeName(propertyType) << propertyType;
            // add converter to cache and return it
            m_serCache.add(propertyType, converter);
            return converter;
        }
    }

    return converter;
}

void KJsonHelpPrivate::updateConverterStore() const
{
    QReadLocker fLocker{&m_typeConverterFactoryLock};
    if (m_typeConverterFactories.size() > m_typeConverters.factoryOffset.loadAcquire())
    {
        QWriteLocker cLocker{&m_typeConverters.lock};
        auto max = m_typeConverterFactories.size();
        for (auto i = m_typeConverters.factoryOffset.loadAcquire(); i < max; ++i)
        {
            auto converter = m_typeConverterFactories[i]->createConverter();
            if (converter)
            {
                converter->setHelper(m_q);
                m_typeConverters.insertSorted(converter, cLocker);
                m_serCache.clear();
                m_deserCache.clear();
                //qCWarning(logSerializer) << "Found and added new global converter:" << converter->name();
            }
        }
        m_typeConverters.factoryOffset.storeRelease(m_typeConverterFactories.size());
    }
}
