#include "testradar.h"
#include <QTimerEvent>
#include <QDebug>
#include <math.h>
using namespace RadarDisplay;

static const int MAX_DISTANCE       = 30000;
static const int TIME_STEP          = 20;
static const float ANTENNA_STEP     = 2.0;
static const int TRACKS_PER_CYCLE   = 180;
static const int LOOP_CYCLES        = 16;
static const float SPEED_STEP       = 800.0;
static const float AZIM_STEP        = 3.0;

TestRadar::TestRadar(QObject *parent) :
    IRadar(parent),
    m_antennaPostion(0.0),
    m_time(0),
    m_nPlot(0),
    m_largeDataSetEnabled(false)
{
    setName(tr("Test", "IRadar"));
    setId("TestRadar");
    m_timerId = startTimer(TIME_STEP);
    generatePlots();
    setLargeDataSetEnabled(true);
}

TestRadar::~TestRadar()
{
    killTimer(m_timerId);
}

int TestRadar::maxDistance() const
{
    return MAX_DISTANCE;
}

float TestRadar::antennaPosition() const
{
    return m_antennaPostion;
}

void TestRadar::setAntennaPosition(float pos)
{
    if (m_antennaPostion != pos) {
        m_antennaPostion = pos;
        emit antennaPositionChanged(pos);
    }
}

void TestRadar::timerEvent(QTimerEvent *event)
{
    float pos;
    Q_UNUSED(event)
    m_time += TIME_STEP;
    pos = m_antennaPostion + ANTENNA_STEP;
    if (pos >= 360.0)
        pos -= 360.0;
    setAntennaPosition(pos);
    updatePlots();
    updateTracks();
    m_nPlot++;
}

void TestRadar::setLargeDataSetEnabled(bool en)
{
    m_largeDataSetEnabled = en;
}

void TestRadar::generatePlots()
{
    m_plots.resize(360.0/ANTENNA_STEP);
    int n = 0;
    qreal pos = 0;
    while (pos < 360.0) {
        float dist, azim, elev, height;
        dist = 1000;
        azim = pos;
        elev = 20.0;
        height = 2000;
        m_plots[n].resize(580);
        for (int i = 0; i < 145; i++) {
            for (int j = 0; j < 4; j++) {
                PlotData plot(i*20 + j, dist + 200 * i, fmod(azim - 0.5*j + 360, 360) , elev, height,
                              QTime(0, 0, 0, 0).msecsTo(QTime::currentTime()));
                m_plots[n].append(plot);
            }
        }

        pos += ANTENNA_STEP;
        n++;
    }
}

void TestRadar::updatePlots()
{
    if (m_largeDataSetEnabled) {
        int idx = m_antennaPostion / ANTENNA_STEP;
        QVector<PlotData> &plots = m_plots[idx];
        for (int i = 0; i < plots.size(); i++) {
            plots[i].milliSeconds = QTime(0, 0, 0, 0).msecsTo(QTime::currentTime());
            emit plotAdded(plots[i]);
        }
    } else {
        if (m_time % 300 != 0)
            return;
        PlotData plot;
        float dist, azim, elev, height;
        int cycles;
        cycles = m_nPlot/TRACKS_PER_CYCLE;
        dist = MAX_DISTANCE/3 + SPEED_STEP*(cycles % LOOP_CYCLES);
        azim = antennaPosition() - 2*AZIM_STEP;
        azim = (azim<0.0)?(azim+360.0):azim;
        elev = 20.0;
        height = 2000;
        plot = PlotData(m_nPlot*2, dist, azim, elev, height, QTime().msecsTo(QTime::currentTime()));
        emit plotAdded(plot);
        plot.id += 1;
        plot.azimuth += AZIM_STEP;
        if (plot.azimuth < 0.0)
            plot.azimuth += 360.0;
        emit plotAdded(plot);
    }
}

void TestRadar::updateTracks()
{
    static TrackData *tracks[TRACKS_PER_CYCLE] = {0};
    TrackData *track;
    int idx;

    if (!m_largeDataSetEnabled) {
        if (m_time % 300 != 0)
            return;
    }
    idx = m_nPlot % TRACKS_PER_CYCLE;
    track = tracks[idx];
    if (!track) {
        track = new TrackData(idx+1);
        tracks[idx] = track;
        emit trackAdded(*track);
    }

    float dist, azim, elev, height;
    int cycles;
    TargetData target;
    cycles = m_nPlot/TRACKS_PER_CYCLE;
    dist = MAX_DISTANCE/3 + SPEED_STEP*(cycles % LOOP_CYCLES);
    azim = antennaPosition() - 1.5*AZIM_STEP;
    azim = (azim<0.0)?(azim+360.0):azim;
    elev = 20.0;
    height = 2000;
    target = TargetData(idx+1, Target_Normal, dist, azim, elev, height, azim, SPEED_STEP,
                        QTime(0, 0, 0, 0).msecsTo(QTime::currentTime()));
    if ((cycles % LOOP_CYCLES == 0) && (cycles > 0)) {
        emit trackRemoved(*tracks[idx]);
        emit trackAdded(*tracks[idx]);
    }
    emit trackTargetAdded(target);
}
