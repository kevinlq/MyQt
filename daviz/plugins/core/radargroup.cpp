#include "radargroup.h"
#include "iradar.h"

using namespace RadarDisplay;
RadarGroup::RadarGroup(QObject *parent) :
    QObject(parent)
{
}

void RadarGroup::addRadar(IRadar *radar)
{
    m_radars.append(radar);
}

void RadarGroup::removeRadar(IRadar *radar)
{
    m_radars.removeOne(radar);
}

QList<IRadar *> RadarGroup::radarList() const
{
    return m_radars;
}
