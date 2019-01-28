#include "replayradar.h"
#include "replayconstants.h"
#include "recorder.h"
#include "plotdata.h"
#include "trackdata.h"
#include "targetdata.h"
#include <QFileInfo>
#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
using namespace  RadarDisplay;

namespace {
static const int DEFAULT_MAX_DISTANCE = 10000;
}

ReplayRadar::ReplayRadar(QObject *parent) :
    IRadar(parent),
    m_baseRadar(0),
    m_antennaPosition(0.0),
    m_state(ReplayRadar::Stopped),
    m_speed(1.0),
    m_hasError(false),
    m_timerId(0)
{
    setId("Radar.Replay");
    setName(tr("ReplayRadar"));
    setUserVisible(false);
}

ReplayRadar::~ReplayRadar()
{
}

IRadar *ReplayRadar::baseRadar() const
{
    return m_baseRadar;
}

void ReplayRadar::setBaseRadar(IRadar *radar)
{
    if (radar == m_baseRadar)
        return;
    stop();
    unload();
    m_baseRadar = radar;
}

int ReplayRadar::maxDistance() const
{
    if (!m_baseRadar)
        return DEFAULT_MAX_DISTANCE;
    return m_baseRadar->maxDistance();
}

float ReplayRadar::antennaPosition() const
{
    return m_antennaPosition;
}

void ReplayRadar::timerEvent(QTimerEvent *)
{
    Q_ASSERT(m_state == ReplayRadar::Running);
    if (m_replayFile.error()) {
        m_hasError = true;
        m_errorMessage = m_replayFile.errorString();
        stop();
        return;
    }
    QDateTime currentRealTime = QDateTime::currentDateTime();
    int elapsed = m_realLastTime.msecsTo(currentRealTime);
    m_realLastTime = currentRealTime;
    m_currentTime = m_currentTime.addMSecs(elapsed * m_speed);
    if (m_currentTime > m_endTime) {
        m_currentTime = m_endTime;
        pause();
        return;
    }

    int dataType;
    qint64 msecs;
    PlotData plot;
    TrackData track;
    TargetData target;
    int pos;
    do {
        pos = m_replayFile.pos();
        m_din >> dataType >> msecs;
        if (msecs < 0 || msecsTotal() < msecs) {
            m_hasError = true;
            m_errorMessage = tr("Bad replay file.");
            stop();
            return;
        }
        // 读太多导致时间超前了，恢复到上次读取位置
        if (m_currentTime <= m_startTime.addMSecs(msecs)) {
            m_replayFile.seek(pos);
            break;
        }
        switch (dataType) {
        case RecordType_AntennaChanged:
            m_din >> m_antennaPosition;
            Q_ASSERT(m_antennaPosition >= 0.0 && m_antennaPosition <= 360.0);
            emit antennaPositionChanged(m_antennaPosition);
            break;
        case RecordType_PlotAdded:
            m_din >> plot;
            emit plotAdded(plot);
            break;
        case RecordType_TrackAdded:
            m_din >> track;
            emit trackAdded(track);
            break;
        case RecordType_TrackRemoved:
            m_din >> track;
            emit trackRemoved(track);
            break;
        case RecordType_TrackTargetAdded:
            m_din >> target;
            emit trackTargetAdded(target);
            break;
        default:
            m_hasError = true;
            m_errorMessage = tr("Bad replay file.");
            stop();
            return;
        }
    } while (!m_replayFile.error() || m_replayFile.atEnd());
}

QString ReplayRadar::replayFile() const
{
    return m_replayFileName;
}

bool ReplayRadar::setReplayFile(const QString &file)
{
    stop();
    unload();
    m_replayFileName = file;
    load();
    emit replayFileChanged(file);
    if (m_hasError)
        return false;
    return true;
}

ReplayRadar::State ReplayRadar::state() const
{
    return m_state;
}

bool ReplayRadar::isRunning() const
{
    return m_state == ReplayRadar::Running;
}

bool ReplayRadar::isPaused() const
{
    return m_state == ReplayRadar::Paused;
}

bool ReplayRadar::isStopped() const
{
    return m_state == ReplayRadar::Stopped;
}

qreal ReplayRadar::speed() const
{
    return m_speed;
}

void ReplayRadar::setSpeed(qreal s)
{
    if (m_speed != s) {
        m_speed = s;
        emit speedChanged(s);
    }
}

void ReplayRadar::advanceMSecs(int msecs)
{
    QDateTime t = m_currentTime.addMSecs(msecs);
    t = qBound(m_startTime, t, m_endTime);
    QElapsedTimer timer;
    timer.start();
    if (m_currentTime != t) {
        m_currentTime = t;
        qint64 posHint = lookupIndex(m_startTime.secsTo(m_currentTime));
        m_replayFile.seek(posHint);

        int dataType;
        qint64 msecs;
        float antenna;
        PlotData plot;
        TrackData track;
        TargetData target;
        do {
            qint64 pos = m_replayFile.pos();
            m_din >> dataType >> msecs;
            if (msecs < 0 || msecsTotal() < msecs) {
                m_hasError = true;
                m_errorMessage = tr("Bad replay file.");
                stop();
                goto LerrOut;
            }
            switch (dataType) {
            case RecordType_AntennaChanged:
                m_din >> antenna;
                break;
            case RecordType_PlotAdded:
                m_din >> plot;
                break;
            case RecordType_TrackAdded:
            case RecordType_TrackRemoved:
                m_din >> track;
                break;
            case RecordType_TrackTargetAdded:
                m_din >> target;
                break;
            default:
                m_hasError = true;
                m_errorMessage = tr("Bad replay file.");
                stop();
                goto LerrOut;
            }
            // 读太多导致时间超前了，恢复到上次读取位置
            if (m_currentTime <= m_startTime.addMSecs(msecs)) {
                m_replayFile.seek(pos);
                break;
            }
        } while (!m_replayFile.error() || m_replayFile.atEnd());
LerrOut:
        m_realLastTime = QDateTime::currentDateTime();
        emit dataCleared();
    }
//    qDebug() << "seek time: " << timer.elapsed() << " ms";
}

bool ReplayRadar::hasError() const
{
    return m_hasError;
}

QString ReplayRadar::errorMessage() const
{
    return m_errorMessage;
}

void ReplayRadar::deactive()
{
    stop();
    unload();
}

QDateTime ReplayRadar::startTime() const
{
    return m_startTime;
}

QDateTime ReplayRadar::endTime() const
{
    return m_endTime;
}

QDateTime ReplayRadar::currentTime() const
{
    return m_currentTime;
}

qint64 ReplayRadar::msecsTotal() const
{
    return m_startTime.msecsTo(m_endTime);
}

qint64 ReplayRadar::msecsElapsed() const
{
    return m_startTime.msecsTo(m_currentTime);
}

qint64 ReplayRadar::msecsRemain() const
{
    return m_currentTime.msecsTo(m_endTime);
}

void ReplayRadar::start()
{
    if (m_state != ReplayRadar::Stopped && m_state != ReplayRadar::Paused)
        return;
    m_timerId = startTimer(20);
    m_state = ReplayRadar::Running;
    m_currentTime = m_startTime;
    m_realStartTime = QDateTime::currentDateTime();
    m_realLastTime = m_realStartTime;
    if (m_replayFile.isOpen())
        m_replayFile.seek(0);
    emit started();
}

void ReplayRadar::pause()
{
    if (m_state != ReplayRadar::Running)
        return;
    if (m_timerId) {
        killTimer(m_timerId);
        m_timerId = 0;
    }
    m_state = ReplayRadar::Paused;
    emit paused();
}

void ReplayRadar::resume()
{
    if (m_state != ReplayRadar::Paused)
        return;
    Q_ASSERT(m_timerId == 0);
    m_state = ReplayRadar::Running;
    m_realLastTime = QDateTime::currentDateTime();
    m_timerId = startTimer(20);
    emit resumed();
}

void ReplayRadar::stop()
{
    if (m_state == ReplayRadar::Stopped)
        return;
    if (m_state == ReplayRadar::Running) {
        if (m_timerId) {
            killTimer(m_timerId);
            m_timerId = 0;
        }
    }
    m_state = ReplayRadar::Stopped;
    setSpeed(1.0);
    m_currentTime = m_endTime;
    emit stopped();
    emit dataCleared();
}

void ReplayRadar::load()
{
    Q_ASSERT(m_state == ReplayRadar::Stopped);
    QString fullPath = QString("%1/%2/%3")
            .arg(qApp->applicationDirPath())
            .arg(REPLAY_DIR_NAME)
            .arg(m_replayFileName);
    m_replayFile.setFileName(fullPath);
    m_replayFile.open(QFile::ReadOnly);
    if (m_replayFile.error() || !m_replayFile.isOpen()) {
        m_hasError = true;
        m_errorMessage = m_replayFile.errorString();
        return;
    }
    m_din.setDevice(&m_replayFile);

    QFileInfo fi(m_replayFile);
    m_startTime = fi.created();
    m_currentTime = m_startTime;
    m_endTime = fi.lastModified();

    readIndexFile();
}

void ReplayRadar::unload()
{
    Q_ASSERT(m_state == ReplayRadar::Stopped);
    m_replayFile.close();
    m_din.setDevice(0);

    m_indexList.clear();

    m_speed = 1.0;
    m_startTime = QDateTime();
    m_endTime = QDateTime();
    m_currentTime = QDateTime();
    m_realStartTime = QDateTime();
    m_realLastTime = QDateTime();
    m_hasError = false;
    m_errorMessage.clear();
}


void ReplayRadar::readIndexFile()
{
    m_indexList.clear();
    QString indexFileName = m_replayFile.fileName();
    indexFileName.chop(4);
    indexFileName.append(".idx");
    QFile indexFile(indexFileName);
    if (!indexFile.exists())
        return;
    bool isOpen = indexFile.open(QFile::ReadOnly);
    if (!isOpen)
        return;
    for (int i = 0; i < indexFile.size(); i += sizeof(qint64)) {
        qint64 pos;
        indexFile.read((char *)&pos, sizeof(qint64));
        m_indexList.append(pos);
    }
}

qint64 ReplayRadar::lookupIndex(int sec)
{
    if (m_indexList.isEmpty())
        return 0;
    if (sec < 0)
        return 0;
    if (sec >= m_indexList.count())
        return m_indexList.last();
    return m_indexList.at(sec);
}
