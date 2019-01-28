#ifndef TESTRADAR_H
#define TESTRADAR_H

#include "testradar_global.h"
#include "core/iradar.h"
#include <QVector>

class QTimerEvent;
namespace RadarDisplay {
class TESTRADAR_EXPORT TestRadar : public IRadar
{
    Q_OBJECT
public:
    explicit TestRadar(QObject *parent = 0);
    
    ~TestRadar();
    int maxDistance() const;
    float antennaPosition() const;
    void setAntennaPosition(float pos);
    void timerEvent(QTimerEvent *event);
    void setLargeDataSetEnabled(bool en);
    
private:
    void generatePlots();
    void updatePlots();
    void updateTracks();
    float m_antennaPostion;
    int m_timerId;
    int m_time;
    int m_nPlot;
    bool m_largeDataSetEnabled;
    QVector<QVector<PlotData> > m_plots;
};
}

#endif // TESTRADAR_H
