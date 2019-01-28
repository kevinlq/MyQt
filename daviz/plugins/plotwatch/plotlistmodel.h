#ifndef PLOTLISTMODEL_H
#define PLOTLISTMODEL_H

#include "plotwatch_global.h"
#include "core/icore.h"
#include <QAbstractTableModel>
#include <QList>

namespace RadarDisplay {
class PLOTWATCH_EXPORT PlotListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PlotListModel(QObject *parent = 0);

    void timerEvent(QTimerEvent *event);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void appendPlot(const PlotData &plot);
    void removeAllPlots();
    void removeFirstPlot();
    int plotCount() const;

signals:
    
public slots:

private:
    // TODO: 使用QCircularBuffer
    QList<PlotData> m_plots;
    int m_lastPlotCount;
};
}
#endif // PLOTLISTMODEL_H
