#ifndef RADARGROUP_H
#define RADARGROUP_H

#include "core_global.h"
#include <QObject>
#include <QList>

namespace RadarDisplay {
class IRadar;
class CORE_EXPORT RadarGroup : public QObject
{
    Q_OBJECT
public:
    explicit RadarGroup(QObject *parent = 0);
    void addRadar(IRadar *radar);
    void removeRadar(IRadar *radar);
    QList<IRadar *> radarList() const;
    
signals:
    
public slots:
    
private:
    QList<IRadar *> m_radars;
};
}
#endif // RADARGROUP_H
