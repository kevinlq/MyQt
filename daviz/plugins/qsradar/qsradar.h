#ifndef QSRADAR_H
#define QSRADAR_H

#include "qsradar_global.h"
#include "iradar.h"
#include <QSet>
#include <QUdpSocket>

class QSRADAR_EXPORT QSRadar : public RadarDisplay::IRadar
{
    Q_OBJECT
public:
    explicit QSRadar(QObject *parent = 0);
    ~QSRadar();
    int maxDistance() const;
    float antennaPosition() const;
    void setAntennaPosition(float pos);

public slots:
    void readPlotData();
    void readAntennaData();
    void readTrackData();

private:
    float m_antennaPosition;
    QUdpSocket m_antennaSocket;
    QUdpSocket m_plotSocket;
    QUdpSocket m_trackSocket;
    QSet<int> m_trackSet;
};

#endif // QSRADAR_H
