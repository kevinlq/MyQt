#include "recentplotwatch.h"
#include "recentplotwatchconfig.h"
#include "plotlistmodel.h"
#include "plotlistview.h"
#include "utils/fancyheaderview.h"
#include <QWidget>
#include <QTableView>
#include <QHeaderView>
#include <QWidgetAction>
#include <QMenu>
#include <QCursor>
#include <QSlider>
#include <QDebug>

using namespace RadarDisplay;

static const int DEFAULT_RECENT_LENGTH = 10;

RecentPlotWatch::RecentPlotWatch(QObject *parent) :
    IPlotWatch(parent),
    m_recentLength(DEFAULT_RECENT_LENGTH),
    m_paused(false)
{
    setIcon(QIcon(":/icons/roll.png"));
    setText(tr("Recent"));
    m_plotListModel = new PlotListModel;
    m_plotListView = new PlotListView;
    m_plotListView->setModel(m_plotListModel);
    setWidget(m_plotListView);
    setAbilities(IPlotWatch::PauseResumeAbility | IPlotWatch::ClearAbility | IPlotWatch::ConfigAbility);
    setState(IPlotWatch::Running);

    m_configMenu = new QMenu;
    m_configWidget = new RecentPlotWatchConfig(m_configMenu);
    QWidgetAction *widgetAction = new QWidgetAction(m_configMenu);
    widgetAction->setDefaultWidget(m_configWidget);
    m_configMenu->addAction(widgetAction);
}

RecentPlotWatch::~RecentPlotWatch()
{
    delete m_configMenu;
}

void RecentPlotWatch::plotRemoveAll()
{
    m_plotListModel->removeAllPlots();
}

void RecentPlotWatch::plotAdded(const PlotData &plot)
{
    if (m_paused)
        return;
    m_plotListModel->appendPlot(plot);
    if (m_plotListModel->plotCount() > m_recentLength) {
        int removeCount = m_plotListModel->plotCount() - m_recentLength;
        for (int i = 0; i < removeCount; i++)
            m_plotListModel->removeFirstPlot();
    }
}

void RecentPlotWatch::pause()
{
    m_paused = true;
    setState(IPlotWatch::Paused);
}

void RecentPlotWatch::resume()
{
    m_paused = false;
    setState(IPlotWatch::Running);
}

void RecentPlotWatch::clear()
{
    int n = m_plotListModel->plotCount();
    for (int i = 0; i < n; i++)
        m_plotListModel->removeFirstPlot();
}

void RecentPlotWatch::config()
{
    m_configWidget->setRecentLength(m_recentLength);
    m_configMenu->exec(QCursor::pos());
    setRecentLength(m_configWidget->recentLength());
}

void RecentPlotWatch::cleanup()
{
}

int RecentPlotWatch::recentLength() const
{
    return m_recentLength;
}

void RecentPlotWatch::setRecentLength(int len)
{
    m_recentLength = len;
    if (m_plotListModel->plotCount() > m_recentLength) {
        int removeCount = m_plotListModel->plotCount() - m_recentLength;
        for (int i = 0; i < removeCount; i++)
            m_plotListModel->removeFirstPlot();
    }
    m_plotListView->updateGeometry();
}
