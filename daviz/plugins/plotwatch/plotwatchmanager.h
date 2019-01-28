#ifndef PLOTWATCHMANAGER_H
#define PLOTWATCHMANAGER_H

#include "plotwatch_global.h"
#include "core/icore.h"
#include <QWidget>
#include <QVector>

class QAction;
class QTabWidget;
class QToolButton;
namespace RadarDisplay {
class IPlotWatch;
class IRadar;
class FancyTabWidget;
class RecentPlotWatch;
class PLOTWATCH_EXPORT PlotWatchManager : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWatchManager(QWidget *parent = 0);
    ~PlotWatchManager();
    void addWatch(IPlotWatch *watch);
    void removeWatch(IPlotWatch *watch);
    IPlotWatch *currentPlotWatch() const;
    void setRadar(IRadar *radar);

signals:
    void currentPlotWatchChanged(IPlotWatch *plotWatch);

public slots:
    void clearData();
    void plotAdded(const PlotData &plot);
    void antennaPositionChanged(float degree);
    void tabCloseRequested(int index);
    void currentTabChanged(int index);
    void toggleRecentPlotWatch(bool toggle);
    
private:
    QToolButton *createAddPlotWatchButton();
    IRadar *m_radar;
    QVector<IPlotWatch *> m_plotWatches;
    FancyTabWidget *m_tabWidget;
    QToolButton *m_addPlotWatchButton;
    QAction *m_showRecentAction;
    RecentPlotWatch *m_recent;
};
}

#endif // PLOTWATCHMANAGER_H
