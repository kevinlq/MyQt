#include "tracklistmodel.h"
#include "core/iradar.h"
#include <QDebug>
#include <QModelIndex>
#include <QString>
#include <QVariant>
#include <QApplication>
#include <QBrush>
#include <limits.h>

using namespace RadarDisplay;

static const int COLUMNS = 8;
static const int COL_ID = 0;
static const int COL_DIST = 1;
static const int COL_AZIM = 2;
static const int COL_ELEV = 3;
static const int COL_HEIGHT = 4;
static const int COL_ORIENT = 5;
static const int COL_SPEED = 6;
static const int COL_TIME = 7;
static const char *COL_TEXTS[] = {
    QT_TRANSLATE_NOOP("TrackListModel", "ID"),
    QT_TRANSLATE_NOOP("TrackListModel", "R"),
    QT_TRANSLATE_NOOP("TrackListModel", "A"),
    QT_TRANSLATE_NOOP("TrackListModel", "E"),
    QT_TRANSLATE_NOOP("TrackListModel", "H"),
    QT_TRANSLATE_NOOP("TrackListModel", "O"),
    QT_TRANSLATE_NOOP("TrackListModel", "V"),
    QT_TRANSLATE_NOOP("TrackListModel", "T"),
};

TrackListModel::TrackListModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_radar(0)
{
    resetChangedRow();

    startTimer(100);
}

Qt::ItemFlags TrackListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TrackListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal)
        return QAbstractTableModel::headerData(section, orientation, role);
    if (role != Qt::DisplayRole)
        return QVariant();
    Q_ASSERT((section >= 0) && (section < COLUMNS));
    return qApp->translate("TrackListModel", COL_TEXTS[section]);
}

QVariant TrackListModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT((index.row() >= 0) && (index.row() < m_targets.size()));
    QTime t(0, 0, 0, 0);
    if (role == Qt::DisplayRole) {
        const TargetData &target = m_targets[index.row()];
        switch (index.column()) {
        case COL_ID:
            return target.trackId;
        case COL_DIST:
            return QString::number(target.distance, 'f', 0);
        case COL_AZIM:
            return QString::number(target.azimuth, 'f', 2);
        case COL_ELEV:
            return QString::number(target.elevation, 'f', 2);
        case COL_HEIGHT:
            return QString::number(target.height, 'f', 0);
        case COL_ORIENT:
            return QString::number(target.orientation, 'f', 2);
        case COL_SPEED:
            return QString::number(target.speed, 'f', 0);
        case COL_TIME:
            t = t.addMSecs(target.milliseconds);
            return t.toString("hh:mm:ss.zzz");
        default:
            Q_ASSERT(0);
        }
    } else if (role == Qt::ForegroundRole) {
        if (index.row() == m_lastChangedRow)
            return QVariant(QBrush(Qt::red));
        else
            return QVariant(QBrush(Qt::black));
    } else if (role == Qt::TextAlignmentRole) {
        return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }

    return QVariant();
}

int TrackListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_trackIds.size();
}

int TrackListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMNS;
}

void TrackListModel::timerEvent(QTimerEvent *)
{
    if (m_layoutChanged)
        emit layoutChanged();
    else {
        if (m_maxChangedRow >= 0)
            emit dataChanged(createIndex(m_minChangedRow, 0),
                             createIndex(m_maxChangedRow, COLUMNS - 1));
    }
    resetChangedRow();
}

void TrackListModel::setRadar(IRadar *radar)
{
    if (m_radar == radar)
        return;
    if (m_radar)
        m_radar->disconnect(this);
    m_radar = radar;
    if (m_radar) {
        connect(m_radar, SIGNAL(dataCleared()), SLOT(clearData()));
        connect(m_radar, SIGNAL(trackAdded(TrackData)), SLOT(trackAdded(TrackData)));
        connect(m_radar, SIGNAL(trackRemoved(TrackData)), SLOT(trackRemoved(TrackData)));
        connect(m_radar, SIGNAL(trackTargetAdded(TargetData)), SLOT(trackTargetAdded(TargetData)));
    }
    clearData();
}

void TrackListModel::clearData()
{
    m_trackIds.clear();
    m_targets.clear();
    resetChangedRow();
    emit layoutChanged();
}

void TrackListModel::trackAdded(const TrackData &trackData)
{
    int row = getRow(trackData.id);
    if (row != -1)
        trackRemoved(trackData);
    m_trackIds.append(trackData.id);
    m_targets.append(TargetData());
    m_layoutChanged = true;
}

void TrackListModel::trackRemoved(const TrackData &trackData)
{
    int row = getRow(trackData.id);
    if (row == -1)
        return;
    if (m_lastChangedRow == row)
        m_lastChangedRow = -1;
    m_trackIds.remove(row);
    m_targets.remove(row);
    m_layoutChanged = true;
}

void TrackListModel::trackTargetAdded(const TargetData &targetData)
{
    int row = getRow(targetData.trackId);
    TrackData trackData(targetData.trackId);
    if (row == -1) {
        trackAdded(trackData);
        row = getRow(trackData.id);
    }
    m_targets[row] = targetData;
    m_lastChangedRow = row;
    if (row < m_minChangedRow)
        m_minChangedRow = row;
    if (m_maxChangedRow < row)
        m_maxChangedRow = row;
}

int TrackListModel::getRow(int trackId)
{
    int foundRow = -1;
    for (int i = 0; i < m_trackIds.size(); i++) {
        if (m_trackIds[i] == trackId) {
            foundRow = i;
            break;
        }
    }
    return foundRow;
}

void TrackListModel::resetChangedRow()
{
    m_minChangedRow = INT_MAX;
    m_maxChangedRow = INT_MIN;
    m_layoutChanged = false;
}

