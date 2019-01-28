#ifndef RECORDER_H
#define RECORDER_H

#include "replay_global.h"
#include "recordtypes.h"
#include "iradar.h"
#include <QObject>
#include <QFile>
#include <QDir>
#include <QTemporaryFile>
#include <QDataStream>
#include <QDateTime>

namespace RadarDisplay {
class REPLAY_EXPORT Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent = 0);
    ~Recorder();
    bool isRecording() const;
    void start();
    void stop();
    QString currentFileName() const;

signals:
    void started();
    void stopped();
    
public slots:
    void currentRadarChanged(IRadar *radar);
    void recordAntennaChanged(float position);
    void recordPlotAdded(const PlotData &plot);
    void recordTrackAdded(const TrackData &track);
    void recordTrackRemoved(const TrackData &track);
    void recordTrackTargetAdded(const TargetData &target);

private:
    void cleanupTempFiles();
    void writeIndexFile();
    void prepareIndex();
    void updateIndex(qint64 msecsElapsed, qint64 filePos);

    bool m_recording;
    IRadar *m_radar;
    QFile m_file;
    QDataStream m_dout;
    QDateTime m_startTime;

    QList<qint64> m_indexList;
};
}

QDataStream &operator <<(QDataStream &dout, const RadarDisplay::PlotData &plot);
QDataStream &operator >>(QDataStream &dout, RadarDisplay::PlotData &plot);

QDataStream &operator <<(QDataStream &dout, const RadarDisplay::TrackData &track);
QDataStream &operator >>(QDataStream &dout, RadarDisplay::TrackData &track);

QDataStream &operator <<(QDataStream &dout, const RadarDisplay::TargetData &target);
QDataStream &operator >>(QDataStream &dout, RadarDisplay::TargetData &target);

#endif // RECORDER_H
