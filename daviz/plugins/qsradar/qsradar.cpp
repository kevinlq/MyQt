#include "qsradar.h"
#include "plotdata.h"
#include "targetdata.h"
#include "trackdata.h"
#include "qsutil.h"
#include "packetformat.h"
#include "xxtrack.h"
#include "iradar.h"
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QUdpSocket>

using namespace RadarDisplay;

static const int MAX_DISTANCE = 20000;
static const int PLOT_PORT = 16000;
static const int ANTENNA_PORT = 17000;
static const int TRACK_PORT = 15000;
static const int MAX_PLOT_BUFFER_SIZE = 65536;

QSRadar::QSRadar(QObject *parent) :
    IRadar(parent),
    m_antennaPosition(0.0)
{
    setName(tr("QSRadar", "IRadar"));
    bool ok = m_antennaSocket.bind(ANTENNA_PORT);
    if (!ok)
        qFatal("unable to bind antenna port %d", ANTENNA_PORT);
    connect(&m_antennaSocket, SIGNAL(readyRead()), SLOT(readAntennaData()));

    ok = m_plotSocket.bind(PLOT_PORT);
    if (!ok)
        qFatal("unable to bind plot port %d", PLOT_PORT);
    connect(&m_plotSocket, SIGNAL(readyRead()), SLOT(readPlotData()));

    ok = m_trackSocket.bind(TRACK_PORT);
    if (!ok)
        qFatal("unable to bind plot port %d", TRACK_PORT);
    connect(&m_trackSocket, SIGNAL(readyRead()), SLOT(readTrackData()));
}

QSRadar::~QSRadar()
{
    qDebug() << Q_FUNC_INFO;
}

int QSRadar::maxDistance() const
{
    return MAX_DISTANCE;
}

float QSRadar::antennaPosition() const
{
    return m_antennaPosition;
}

void QSRadar::setAntennaPosition(float pos)
{
    if (m_antennaPosition != pos) {
        m_antennaPosition = pos;
        emit antennaPositionChanged(pos);
    }
}

void QSRadar::readPlotData()
{
    static char buf[MAX_PLOT_BUFFER_SIZE];
    qint64 len;
    len = m_plotSocket.readDatagram(buf, MAX_PLOT_BUFFER_SIZE);
    if (len <= 0)
        return;

    if ((len % sizeof(CPointPacket)) != 0) {
        qDebug() << "Not a valid cpointpacket" << len << sizeof(CPointPacket)
                 << m_plotSocket.pendingDatagramSize();
        return;
    }

    int packetCount = len / sizeof(CPointPacket);
    const CPointPacket *cp = (const CPointPacket *)buf;
    for (int i = 0; i < packetCount; i++) {
        float elevation;
        elevation = eswapFloat(&cp->elevation) / 100;
        PlotData plot(cp->pointNumber, cp->distance, cp->azimuth*360.0/8192, elevation,
                      /* height = */ 0.0, cp->timeMilliSecond);
        emit plotAdded(plot);
        cp++;
    }
}

void QSRadar::readAntennaData()
{
    static quint8 buf[4];
    qint64 len;
    float azim;
    len = m_antennaSocket.readDatagram((char*)buf, 4);
    if (len <= 0)
        return;
    azim = (buf[0] << 8) + buf[1];
    setAntennaPosition(azim);
}

void QSRadar::readTrackData()
{
    static quint8 buf[100];
    qint64 len;
    len = m_trackSocket.readDatagram((char*)buf, 100);
    if (len <= 0)
        return;
    if (len != sizeof(TrackUpdatePacket)) {
        qDebug() << "Not a valid cpointpacket" << len << sizeof(TrackUpdatePacket) << m_trackSocket.hasPendingDatagrams();
        return;
    }
    TrackUpdatePacket *tup = (TrackUpdatePacket *)buf;
    TrackPacket *tp;
    TrackData trackData;
    TargetData targetData;
    QTime time;
    switch (tup->type) {
    case TrackUpdate_New:
        trackData.id = tup->body.newTrackNumber;
        if (m_trackSet.contains(trackData.id)) {
            m_trackSet.remove(trackData.id);
            emit trackRemoved(trackData);
        }
        m_trackSet.insert(trackData.id);
        emit trackAdded(trackData);
        break;
    case TrackUpdate_Update:
        tp = &tup->body.trackPacket;
        if (tp->pointNumber == 0)
            break;
        targetData.trackId = tup->body.trackPacket.trackNumber;
        targetData.type = Target_Normal;
        targetData.distance = tp->distance;
        targetData.azimuth = tp->azimuth * AZIM_UNIT;
        targetData.elevation = tp->elevation / 100.0;
        targetData.height = tp->height;
        targetData.orientation = tp->orientation;
        targetData.speed = tp->speed / 10.0;
        targetData.milliseconds = tp->timeMilliSecond;

        if (!m_trackSet.contains(targetData.trackId)) {
            m_trackSet.insert(targetData.trackId);
            trackData.id = targetData.trackId;
            emit trackAdded(trackData);
        }

        emit trackTargetAdded(targetData);
        break;
    case TrackUpdate_Lost:
        trackData.id = tup->body.lostTrackNumber;
        m_trackSet.remove(trackData.id);
        emit trackRemoved(trackData);
        break;
    default:
        Q_ASSERT(0);
    }
}
