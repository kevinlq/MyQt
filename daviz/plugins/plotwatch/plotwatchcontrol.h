#ifndef PLOTWATCHCONTROL_H
#define PLOTWATCHCONTROL_H

#include <QWidget>

class QToolButton;
class QAction;
namespace RadarDisplay {
class PlotWatchManager;
class IPlotWatch;
class PlotWatchControl : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWatchControl(PlotWatchManager *pm, QWidget *parent = 0);
    virtual ~PlotWatchControl();

public slots:
    void currentPlotWatchChanged(IPlotWatch *watch);
    void plotWatchPauseResume();
    void plotWatchClear();
    void plotWatchConfig();

private:
    PlotWatchManager *m_pm;
    QAction *m_pauseResumeAction;
    QAction *m_clearAction;
    QAction *m_configAction;
};
}
#endif // PLOTWATCHCONTROL_H
