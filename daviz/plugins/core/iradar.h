#ifndef IRADAR_H
#define IRADAR_H

#include "core_global.h"
#include "trackdata.h"
#include "plotdata.h"
#include "targetdata.h"
#include <QObject>
#include <QString>
#include <QMetaType>

namespace RadarDisplay {
class CORE_EXPORT IRadar : public QObject
{
    Q_OBJECT
public:
    IRadar(QObject *parent = 0);
    virtual ~IRadar();
    QString id() const;
    void setId(const QString &id);
    QString name() const;
    void setName(const QString &name);
    bool isUserVisible() const;
    void setUserVisible(bool visible);
    virtual int maxDistance() const = 0;
    virtual float antennaPosition() const = 0;
    virtual void active();
    virtual void deactive();

signals:
    void dataCleared();
    void antennaPositionChanged(float degree);
    void plotAdded(const PlotData &plot);
    void trackAdded(const TrackData &track);
    void trackRemoved(const TrackData &track);
    void trackTargetAdded(const TargetData &target);

private:
    QString m_id;
    QString m_name;
    bool m_userVisible;
};
}
Q_DECLARE_METATYPE(RadarDisplay::IRadar *)

#endif // IRADAR_H
