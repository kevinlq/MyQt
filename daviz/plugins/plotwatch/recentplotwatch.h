#ifndef RECENTPLOTWATCH_H
#define RECENTPLOTWATCH_H

#include "iplotwatch.h"

class QTableView;
class QMenu;
namespace RadarDisplay {
class PlotListModel;
class PlotListView;
class RecentPlotWatchConfig;
class RecentPlotWatch : public IPlotWatch
{
    Q_OBJECT
public:
    explicit RecentPlotWatch(QObject *parent = 0);
    ~RecentPlotWatch();

    void plotRemoveAll();

    void plotAdded(const PlotData &plot);

    void pause();
    void resume();
    void clear();
    void config();

    void cleanup();

    int recentLength() const;
    void setRecentLength(int len);

signals:
    
public slots:
    
private:
    IRadar *m_radar;
    int m_recentLength;
    PlotListView *m_plotListView;
    PlotListModel *m_plotListModel;
    bool m_paused;
    QMenu *m_configMenu;
    RecentPlotWatchConfig *m_configWidget;
};
}

#endif // RECENTPLOTWATCH_H
