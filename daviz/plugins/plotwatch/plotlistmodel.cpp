#include "plotlistmodel.h"
#include <QApplication>
#include <QDebug>

using namespace RadarDisplay;

static const int COLUMNS = 6;
static const int COL_ID = 0;
static const int COL_DIST = 1;
static const int COL_AZIM = 2;
static const int COL_ELEV = 3;
static const int COL_HEIGHT = 4;
static const int COL_TIME = 5;
static const char *COL_TEXTS[] = {
    QT_TRANSLATE_NOOP("PlotListModel", "ID"),
    QT_TRANSLATE_NOOP("PlotListModel", "R"),
    QT_TRANSLATE_NOOP("PlotListModel", "A"),
    QT_TRANSLATE_NOOP("PlotListModel", "E"),
    QT_TRANSLATE_NOOP("PlotListModel", "H"),
    QT_TRANSLATE_NOOP("PlotListModel", "T"),
};

PlotListModel::PlotListModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_lastPlotCount(0)
{
    startTimer(100);
}

void PlotListModel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    int plotCount = m_plots.size();
    if (m_lastPlotCount == plotCount) {
        emit dataChanged(createIndex(0, 0), createIndex(plotCount - 1, columnCount() - 1));
    } else if (m_lastPlotCount < plotCount) {
        beginInsertRows(QModelIndex(), m_lastPlotCount, plotCount - 1);
        endInsertRows();
    } else /* m_lastPlotCount > plotCount */ {
        beginRemoveRows(QModelIndex(), 0, m_lastPlotCount - plotCount - 1);
        endRemoveRows();
    }
    m_lastPlotCount = plotCount;
    /*
    beginResetModel();
    endResetModel();
    */
}

Qt::ItemFlags PlotListModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant PlotListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal)
        return QAbstractTableModel::headerData(section, orientation, role);
    if (role == Qt::DisplayRole) {
        return qApp->translate("PlotListModel", COL_TEXTS[section]);
    }

    return QVariant();
}

QVariant PlotListModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT((index.row() >= 0) && (index.row() < m_plots.size()));
    QTime time(0, 0, 0, 0);
    if (role == Qt::DisplayRole) {
        const PlotData &plot = m_plots[index.row()];
        switch (index.column()) {
        case COL_ID:
            return plot.id;
        case COL_DIST:
            return QString::number(plot.distance, 'f', 0);
        case COL_AZIM:
            return QString::number(plot.azimuth, 'f', 2);
        case COL_ELEV:
            return QString::number(plot.elevation, 'f', 2);
        case COL_HEIGHT:
            return QString::number(plot.height, 'f', 0);
        case COL_TIME:
            time = time.addMSecs(plot.milliSeconds);
            return time.toString("hh:mm:ss.zzz");
        default:
            Q_ASSERT(0);
        }
    } else if (role == Qt::TextAlignmentRole) {
        return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }

    return QVariant();
}

int PlotListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_plots.size();
}

int PlotListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMNS;
}

void PlotListModel::removeAllPlots()
{
    m_plots.clear();
}

void PlotListModel::appendPlot(const PlotData &plot)
{
//    beginInsertRows(QModelIndex(), plotCount(), plotCount());
    m_plots.append(plot);
    //    endInsertRows();
}

void PlotListModel::removeFirstPlot()
{
    m_plots.removeFirst();
}

int PlotListModel::plotCount() const
{
    return m_plots.size();
}
