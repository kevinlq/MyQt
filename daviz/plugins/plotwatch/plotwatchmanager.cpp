#include "plotwatchmanager.h"
#include "plotwatchcontrol.h"
#include "iplotwatch.h"
#include "recentplotwatch.h"
#include "utils/fancytabwidget.h"
#include "core/iradar.h"
#include <QHBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QTabBar>
#include <QToolButton>
#include <QMenu>
#include <QIcon>
#include <QApplication>

using namespace RadarDisplay;

static const char DIALOG_WARNING_ICON[] = ":/icons/dialog-warning.png";

PlotWatchManager::PlotWatchManager(QWidget *parent) :
    QWidget(parent),
    m_radar(0)
{
    m_tabWidget = new FancyTabWidget(this);
    m_tabWidget->setPlaceHolder(new QLabel(tr("No activated plot watches."), this),
                                QIcon(DIALOG_WARNING_ICON),
                                tr("Plot Watch"));
    m_tabWidget->setTabsClosable(true);
    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->setCornerWidget(new PlotWatchControl(this), Qt::BottomLeftCorner);
    m_addPlotWatchButton = createAddPlotWatchButton();
    m_tabWidget->setCornerWidget(m_addPlotWatchButton, Qt::BottomRightCorner);
    connect(m_tabWidget, SIGNAL(tabCloseRequested(int)), SLOT(tabCloseRequested(int)));
    connect(m_tabWidget, SIGNAL(currentChanged(int)), SLOT(currentTabChanged(int)));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_tabWidget);

    m_recent = new RecentPlotWatch(this);
    addWatch(m_recent);
}

PlotWatchManager::~PlotWatchManager()
{
    while (!m_plotWatches.isEmpty()) {
        removeWatch(m_plotWatches.first());
    }
}

void PlotWatchManager::addWatch(IPlotWatch *watch)
{
    Q_ASSERT(watch->widget());
    m_plotWatches.append(watch);
    m_tabWidget->addTab(watch->widget(), watch->icon(), watch->text());
}

void PlotWatchManager::removeWatch(IPlotWatch *watch)
{
    int index = m_plotWatches.indexOf(watch);
    if (index == -1)
        return;
    m_plotWatches.remove(index);
    int tabIndex = m_tabWidget->indexOf(watch->widget());
    if (tabIndex != -1)
        m_tabWidget->removeTab(tabIndex);
    watch->cleanup();
}

IPlotWatch *PlotWatchManager::currentPlotWatch() const
{
    QWidget *widget = m_tabWidget->currentWidget();
    if (!widget)
        return 0;
    foreach (IPlotWatch *watch, m_plotWatches) {
        if (widget == watch->widget())
            return watch;
    }
    return 0;
}

void PlotWatchManager::setRadar(IRadar *radar)
{
    if (m_radar == radar)
        return;
    if (m_radar)
        m_radar->disconnect(this);
    m_radar = radar;
    if (m_radar) {
        connect(m_radar, SIGNAL(dataCleared()), SLOT(clearData()));
        connect(m_radar, SIGNAL(plotAdded(PlotData)), SLOT(plotAdded(PlotData)));
        connect(m_radar, SIGNAL(antennaPositionChanged(float)), SLOT(antennaPositionChanged(float)));
    }
    clearData();
}

void PlotWatchManager::clearData()
{
    foreach (IPlotWatch *watch, m_plotWatches) {
        watch->plotRemoveAll();
    }
}

void PlotWatchManager::plotAdded(const PlotData &plot)
{
    foreach (IPlotWatch *watch, m_plotWatches) {
        watch->plotAdded(plot);
    }
}

void PlotWatchManager::antennaPositionChanged(float degree)
{
    foreach (IPlotWatch *watch, m_plotWatches) {
        watch->antennaPositionChanged(degree);
    }
}

void PlotWatchManager::tabCloseRequested(int index)
{
    if (m_plotWatches[index] == m_recent)
        m_showRecentAction->setChecked(false);
    else
        removeWatch(m_plotWatches[index]);
}

void PlotWatchManager::currentTabChanged(int index)
{
    QWidget *widget = m_tabWidget->widget(index);
    if (!widget)
        emit currentPlotWatchChanged(0);
    bool found = false;
    foreach (IPlotWatch *watch, m_plotWatches) {
        if (widget == watch->widget()) {
            emit currentPlotWatchChanged(watch);
            found = true;
            break;
        }
    }
    // 当m_tabWidget为空时会插入一个表示占位符的TabPage，这时候found不成功
    if (!found)
        emit currentPlotWatchChanged(0);
}

void PlotWatchManager::toggleRecentPlotWatch(bool toggle)
{
    if (toggle) {
        if (m_plotWatches.contains(m_recent))
            return;
        addWatch(m_recent);
    } else {
        int index = m_plotWatches.indexOf(m_recent);
        if (index == -1)
            return;
        removeWatch(m_recent);
    }
}

QToolButton *PlotWatchManager::createAddPlotWatchButton()
{
    m_addPlotWatchButton = new QToolButton(this);
    m_addPlotWatchButton->setIcon(QIcon(":/icons/list-add.png"));
    QMenu *menu = new QMenu(this);
    m_showRecentAction = menu->addAction(tr("Show recent"));
    m_showRecentAction->setCheckable(true);
    m_showRecentAction->setChecked(true);
    connect(m_showRecentAction, SIGNAL(toggled(bool)), SLOT(toggleRecentPlotWatch(bool)));
    menu->addAction(m_showRecentAction);
    m_addPlotWatchButton->setMenu(menu);
    m_addPlotWatchButton->setPopupMode(QToolButton::InstantPopup);
    return m_addPlotWatchButton;
}
