#ifndef REPLAYRADAR_H
#define REPLAYRADAR_H

#include "iradar.h"
#include "replay_global.h"
#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QDataStream>
#include <QStringList>

namespace RadarDisplay {

class REPLAY_EXPORT ReplayRadar : public IRadar
{
    Q_OBJECT
public:
    enum State {
        Running,
        Paused,
        Stopped
    };

    ReplayRadar(QObject *parent = 0);
    ~ReplayRadar();

    IRadar *baseRadar() const;
    void setBaseRadar(IRadar *radar);

    int maxDistance() const;
    float antennaPosition() const;
    void deactive();

    QString replayFile() const;
    bool setReplayFile(const QString &file);

    State state() const;
    bool isRunning() const;
    bool isPaused() const;
    bool isStopped() const;

    qreal speed() const;
    void setSpeed(qreal s);

    void advanceMSecs(int msecs);

    bool hasError() const;
    QString errorMessage() const;

    QDateTime startTime() const;
    QDateTime endTime() const;
    QDateTime currentTime() const;
    qint64 msecsTotal() const;
    qint64 msecsElapsed() const;
    qint64 msecsRemain() const;

    void timerEvent(QTimerEvent *);

signals:
    void started();
    void stopped();
    void paused();
    void resumed();
    void speedChanged(qreal speed);
    void replayFileChanged(const QString &file);

public slots:
    void start();
    void pause();
    void resume();
    void stop();

private:
    void load();
    void readIndexFile();
    qint64 lookupIndex(int sec);
    void unload();

    IRadar *m_baseRadar;
    float m_antennaPosition;

    QString m_replayFileName;
    QFile m_replayFile;
    QDataStream m_din;

    State m_state;

    qreal m_speed;

    QDateTime m_startTime;
    QDateTime m_endTime;
    QDateTime m_currentTime;

    QDateTime m_realStartTime;
    QDateTime m_realLastTime;

    bool m_hasError;
    QString m_errorMessage;

    int m_timerId;

    QList<int> m_indexList;
};

} // namespace RadarDisplay
#endif // REPLAYRADAR_H
