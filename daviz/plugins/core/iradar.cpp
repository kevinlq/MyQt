#include "iradar.h"
#include <QMetaObject>
#include <QString>
using namespace RadarDisplay;

IRadar::IRadar(QObject *parent) :
    QObject(parent),
    m_userVisible(true)
{
}

IRadar::~IRadar()
{
}

QString IRadar::id() const
{
    if (m_id.isNull())
        return metaObject()->className();
    else
        return m_id;
}

void IRadar::setId(const QString &id)
{
    m_id = id;
}

QString IRadar::name() const
{
    if (m_name.isNull())
        return metaObject()->className();
    else
        return m_name;
}

void IRadar::setName(const QString &name)
{
    m_name = name;
}

bool IRadar::isUserVisible() const
{
    return m_userVisible;
}

void IRadar::setUserVisible(bool visible)
{
    m_userVisible = visible;
}

void IRadar::active()
{
}

void IRadar::deactive()
{
}


