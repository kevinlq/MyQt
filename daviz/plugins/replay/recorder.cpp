#include "recorder.h"
#include "recordtypes.h"
#include "replayconstants.h"
#include "icore.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>

using namespace RadarDisplay;

Recorder::Recorder(QObject *parent) :
    QObject(parent),
    m_recording(false),
    m_radar(0)
{
    currentRadarChanged(ICore::currentRadar());
    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(currentRadarChanged(IRadar*)));
}

Recorder::~Recorder()
{
    cleanupTempFiles();
}

bool Recorder::isRecording() const
{
    return m_recording;
}

QString Recorder::currentFileName() const
{
    return m_file.fileName();
}

void Recorder::currentRadarChanged(IRadar *radar)
{
    if (m_radar == radar)
        return;
    stop();
    m_radar = radar;
    if (m_recording)
        start();
}

void Recorder::recordAntennaChanged(float position)
{
    qint64 t = m_startTime.msecsTo(QDateTime::currentDateTime());
    updateIndex(t, m_file.pos());
    m_dout << RecordType_AntennaChanged << t;
    m_dout << position;
}

void Recorder::recordPlotAdded(const PlotData &plot)
{
    qint64 t = m_startTime.msecsTo(QDateTime::currentDateTime());
    updateIndex(t, m_file.pos());
    m_dout << RecordType_PlotAdded << t;
    m_dout << plot;
}

void Recorder::recordTrackAdded(const TrackData &track)
{
    qint64 t = m_startTime.msecsTo(QDateTime::currentDateTime());
    updateIndex(t, m_file.pos());
    m_dout << RecordType_TrackAdded << t;
    m_dout << track;
}

void Recorder::recordTrackRemoved(const TrackData &track)
{
    qint64 t = m_startTime.msecsTo(QDateTime::currentDateTime());
    updateIndex(t, m_file.pos());
    m_dout << RecordType_TrackRemoved << t;
    m_dout << track;
}

void Recorder::recordTrackTargetAdded(const TargetData &target)
{
    qint64 t = m_startTime.msecsTo(QDateTime::currentDateTime());
    updateIndex(t, m_file.pos());
    m_dout << RecordType_TrackTargetAdded << t;
    m_dout << target;
}

void Recorder::start()
{
    if (!m_radar)
        return;
    if (m_recording)
        return;

    connect(m_radar, SIGNAL(antennaPositionChanged(float)), SLOT(recordAntennaChanged(float)));
    connect(m_radar, SIGNAL(plotAdded(PlotData)), SLOT(recordPlotAdded(PlotData)));
    connect(m_radar, SIGNAL(trackAdded(TrackData)), SLOT(recordTrackAdded(TrackData)));
    connect(m_radar, SIGNAL(trackRemoved(TrackData)), SLOT(recordTrackRemoved(TrackData)));
    connect(m_radar, SIGNAL(trackTargetAdded(TargetData)), SLOT(recordTrackTargetAdded(TargetData)));

    m_recording = true;
    m_startTime = QDateTime::currentDateTime();
    QString fname = QString("%1/%2/%3.%4")
            .arg(qApp->applicationDirPath())
            .arg(REPLAY_DIR_NAME)
            .arg(m_radar->id())
            .arg(m_startTime.toString("yyyy-MM-dd_hh'h'mm'm'ss's.tmp'"));
    m_file.setFileName(fname);
    m_file.open(QFile::WriteOnly | QFile::Truncate);
    m_dout.setDevice(&m_file);

    prepareIndex();

    emit started();
}

void Recorder::stop()
{
    if (!m_radar)
        return;
    if (!m_recording)
        return;
    m_recording = false;
    m_radar->disconnect(this);

    m_file.close();
    m_dout.setDevice(0);

    QString newFileName = m_file.fileName();
    newFileName.chop(4);
    newFileName.append(".dat");
    m_file.rename(newFileName);

    writeIndexFile();

    emit stopped();
}

void Recorder::cleanupTempFiles()
{
    QDir d(qApp->applicationDirPath());
    d.cd(REPLAY_DIR_NAME);
    d.setNameFilters(QStringList() << "*.tmp");
    foreach (const QString &fname, d.entryList()) {
        d.remove(fname);
    }
}

void Recorder::writeIndexFile()
{
    QString indexFileName = m_file.fileName();
    indexFileName.chop(4);
    indexFileName.append(".idx");
    QFile indexFile(indexFileName);
    indexFile.open(QFile::WriteOnly | QFile::Truncate);
    foreach (qint64 pos, m_indexList) {
        indexFile.write((char *)&pos, sizeof(qint64));
    }
    indexFile.close();
}

void Recorder::prepareIndex()
{
    m_indexList.clear();
    m_indexList << 0;
}

void Recorder::updateIndex(qint64 msecsElapsed, qint64 filePos)
{
    if (msecsElapsed / 1000 >= m_indexList.count())
        m_indexList << filePos;
}

QDataStream &operator <<(QDataStream &dout, const RadarDisplay::PlotData &plot)
{
    dout.writeRawData((char *)&plot, sizeof(RadarDisplay::PlotData));
    return dout;
}

QDataStream &operator >>(QDataStream &dout, RadarDisplay::PlotData &plot)
{
    dout.readRawData((char *)&plot, sizeof(RadarDisplay::PlotData));
    return dout;
}

QDataStream &operator <<(QDataStream &dout, const RadarDisplay::TrackData &track)
{
    dout.writeRawData((char *)&track, sizeof(RadarDisplay::TrackData));
    return dout;
}

QDataStream &operator >>(QDataStream &dout, RadarDisplay::TrackData &track)
{
    dout.readRawData((char *)&track, sizeof(RadarDisplay::TrackData));
    return dout;
}

QDataStream &operator <<(QDataStream &dout, const RadarDisplay::TargetData &target)
{
    dout.writeRawData((char *)&target, sizeof(RadarDisplay::TargetData));
    return dout;
}

QDataStream &operator >>(QDataStream &dout, RadarDisplay::TargetData &target)
{
    dout.readRawData((char *)&target, sizeof(RadarDisplay::TargetData));
    return dout;
}
