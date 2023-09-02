
#pragma once

#include <QString>
#include <QMetaType>
#include <QJsonArray>
#include <QVariant>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QFile>
#include <QTemporaryFile>
#include <QDir>
#include <QRect>
#include <QRect>
#include <QPoint>
#include <QPointF>
#include <QPolygon>
#include <QLine>
#include <QUuid>
#include <QTextStream>
#include <QDebug>
#include <QVarLengthArray>
#include <QReadWriteLock>
#include <QException>

#include "KSerializationHelper.h"

namespace KHelpUtils {
template <class Rect>
static inline QVariant serializeRect(const Rect &r)
{
    return QVariant(QJsonArray{r.x(), r.y(), r.width(), r.height()});
}
template <class Rect>
static inline Rect deserializeRect(const QJsonArray &array)
{
    Rect r(-1, -1, -1, -1);
    if(4 == array.size())
    {
        auto x      = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto y      = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        auto width  = (array[2].type() == QJsonValue::Double) ? array[2].toDouble(-1) : array[2].toInt(-1);
        auto height = (array[3].type() == QJsonValue::Double) ? array[3].toDouble(-1) : array[3].toInt(-1);
        r = Rect(x, y, width, height);
    }
    return r;
}

template <class Size>
static inline QVariant serializeSize(const Size &size)
{
    return QVariant(QJsonArray{size.width(), size.height()});
}
template <class Size>
static inline Size deserializeSize(const QJsonArray &array)
{
    Size s(-1, -1);
    if(2 == array.size())
    {
        auto width  = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto height = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        s.setWidth(width);
        s.setHeight(height);
    }
    return s;
}

template <class Point>
static inline QVariant serializePoint(const Point &point)
{
    return QVariant(QJsonArray{point.x(), point.y()});
}
template <class Point>
static inline Point deserializePoint(const QJsonArray &array)
{
    Point p(-1, -1);
    if(2 == array.size())
    {
        auto x = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto y = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        p.setX(x);
        p.setY(y);
    }
    return p;
}

template <class Polygon>
static inline QJsonArray formatQPolygon(const Polygon &a)
{
    QJsonArray jsArray;
    for (int i = 0; i < a.count(); ++i)
    {
        jsArray << formatQPoint(a.at(i));
    }
    return jsArray;
}
template <class Polygon, class Point>
static inline Polygon toQPolygon(const QJsonArray &array)
{
    Polygon p;
    for (int i = 0; i < array.count(); ++i)
    {
        p << toQPoint<Point>(array.at(i).toArray());
    }
    return p;
}

template <class Line>
static inline QVariant serializeLine(const Line &p)
{
    return QVariant(QJsonArray{p.x1(), p.y1(), p.x2(), p.y2()});
}
template <class Line>
static inline Line deserializeLine(const QJsonArray &array)
{
    Line l(-1, -1, -1, -1);
    if(4 == array.size())
    {
        auto x1 = (array[0].type() == QJsonValue::Double) ? array[0].toDouble(-1) : array[0].toInt(-1);
        auto y1 = (array[1].type() == QJsonValue::Double) ? array[1].toDouble(-1) : array[1].toInt(-1);
        auto x2 = (array[2].type() == QJsonValue::Double) ? array[2].toDouble(-1) : array[2].toInt(-1);
        auto y2 = (array[3].type() == QJsonValue::Double) ? array[3].toDouble(-1) : array[3].toInt(-1);
        l = Line(x1, y1, x2, y2);
    }
    return l;
}

}// namespace KHelpUtils

class Exception : public QException
{
public:
    Exception(const QByteArray &what);
    const char *what() const noexcept final;

    virtual void raise() const override;
    virtual Exception *clone() const override;
private:
    QByteArray m_what;
};

class TypeConverter
{
    Q_DISABLE_COPY(TypeConverter)
public:
    TypeConverter() = default;
    virtual ~TypeConverter() = default;

    int priority() const {return 0;}

    const SerializationHelper *helper() const {return m_pHelper;}

    void setHelper(const SerializationHelper *helper){m_pHelper = helper;}

    virtual bool canConvert(int metaTypeId) const = 0;
    virtual QVariant serialize(int propertyType, const QVariant &value) const = 0;
    virtual QVariant deserialize(int propertyType, const QVariant &value) const = 0;

private:
    const SerializationHelper *m_pHelper = nullptr;
};

// QObject converter
class QObjectConverter : public TypeConverter
{
public:
    bool canConvert(int metaTypeId) const  override;
    QVariant serialize(int propertyType, const QVariant &value) const override;
    QVariant deserialize(int propertyType, const QVariant &value) const override;
};

// geometry converter
class GeometryConverter : public TypeConverter
{
public:
    bool canConvert(int metaTypeId) const  override;
    QVariant serialize(int propertyType, const QVariant &value) const override;
    QVariant deserialize(int propertyType, const QVariant &value) const override;
};

class TypeConverterFactory
{
    Q_DISABLE_COPY(TypeConverterFactory)

public:
    TypeConverterFactory() = default;
    virtual ~TypeConverterFactory() = default;

    //! The primary factory method to create converters
    virtual QSharedPointer<TypeConverter> createConverter() const = 0;
};

template <typename TConverter>
class TypeConverterStandardFactory : public TypeConverterFactory
{
public:
    QSharedPointer<TypeConverter> createConverter() const override;
};
template<typename TConverter>
QSharedPointer<TypeConverter> TypeConverterStandardFactory<TConverter>::createConverter() const
{
    return QSharedPointer<TConverter>::create();
}

template <typename TConverter>
class ThreadSafeStore {
public:
    ThreadSafeStore() = default;
    ThreadSafeStore(std::initializer_list<std::pair<int, QSharedPointer<TConverter>>> initData);

    QSharedPointer<TConverter> get(int metaTypeId) const;
    void add(int metaTypeId, const QSharedPointer<TConverter> &converter);

    void clear();

private:
    mutable QReadWriteLock _lock {};
    QHash<int, QSharedPointer<TConverter>> _store;
};
template<typename TConverter>
ThreadSafeStore<TConverter>::ThreadSafeStore(std::initializer_list<std::pair<int, QSharedPointer<TConverter> > > initData)
 : _store{std::move(initData)}{}
template<typename TConverter>
QSharedPointer<TConverter> ThreadSafeStore<TConverter>::get(int metaTypeId) const
{
    QReadLocker _{&_lock};
    return _store.value(metaTypeId, nullptr);
}

template<typename TConverter>
void ThreadSafeStore<TConverter>::add(int metaTypeId, const QSharedPointer<TConverter> &converter)
{
    QWriteLocker _{&_lock};
    _store.insert(metaTypeId, converter);
}

template<typename TConverter>
void ThreadSafeStore<TConverter>::clear()
{
    QWriteLocker _{&_lock};
    _store.clear();
}
template <typename TConverter>
struct ConverterStore
{
    mutable QReadWriteLock lock {};
    QList<QSharedPointer<TConverter>> store;
    QAtomicInt factoryOffset = 0;

    ConverterStore() = default;
    ConverterStore(std::initializer_list<QSharedPointer<TConverter>> initData);

    void insertSorted(const QSharedPointer<TConverter> &converter);
    void insertSorted(const QSharedPointer<TConverter> &converter, QWriteLocker &locker);
};
template<typename TConverter>
ConverterStore<TConverter>::ConverterStore(std::initializer_list<QSharedPointer<TConverter>> initData)
    : store{std::move(initData)}
{
#ifndef QT_NO_DEBUG
    for (auto i = 1; i < store.size(); ++i)
        Q_ASSERT(store[i]->priority() <= store[i - 1]->priority());
#endif
}

template<typename TConverter>
void ConverterStore<TConverter>::insertSorted(const QSharedPointer<TConverter> &converter)
{
    QWriteLocker _{&lock};
    insertSorted(converter, _);
}

template<typename TConverter>
void ConverterStore<TConverter>::insertSorted(const QSharedPointer<TConverter> &converter, QWriteLocker &locker)
{
    Q_UNUSED(locker)
    for (auto it = store.begin(); it != store.end(); ++it) {
        if ((*it)->priority() < converter->priority()) {
            store.insert(it, converter);
            return;
        }
    }
    // not inserted -> add to end
    store.append(converter);
}

class KJsonHelpPrivate
{
public:
    KJsonHelpPrivate(SerializationHelper* parent);
    ~KJsonHelpPrivate();

    QSharedPointer<TypeConverter> findSerConverter(int propertyType) const;

    void updateConverterStore() const;
public:
    static QReadWriteLock m_typeConverterFactoryLock;
    static QList<TypeConverterFactory*> m_typeConverterFactories;

    mutable ConverterStore<TypeConverter> m_typeConverters;
    mutable ThreadSafeStore<TypeConverter> m_serCache;
    mutable ThreadSafeStore<TypeConverter> m_deserCache;

private:
private:
    SerializationHelper *m_q = nullptr;
};
