#ifndef TRACKLISTMODEL_H
#define TRACKLISTMODEL_H

#include "tracklistview_global.h"
#include "core/icore.h"
#include <QAbstractTableModel>
#include <QVector>
#include <QObject>

namespace RadarDisplay {
class IRadar;
class TRACKLISTVIEW_EXPORT TrackListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TrackListModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void timerEvent(QTimerEvent *);

    void setRadar(IRadar *radar);

public slots:
    void clearData();
    void trackAdded(const TrackData &trackData);
    void trackRemoved(const TrackData &trackData);
    void trackTargetAdded(const TargetData &targetData);

private:
    int getRow(int trackId);
    void resetChangedRow();
    int m_lastChangedRow;
    int m_minChangedRow;
    int m_maxChangedRow;
    bool m_layoutChanged;
    IRadar *m_radar;
    QVector<TargetData> m_targets;
    QVector<int> m_trackIds;
};
}
#endif // TRACKLISTMODEL_H
