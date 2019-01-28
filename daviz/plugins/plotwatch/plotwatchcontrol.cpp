#include "plotwatchcontrol.h"
#include "plotwatchmanager.h"
#include "iplotwatch.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QIcon>
#include <QAction>
#include <QByteArray>
#include <QVariant>
#include <QDebug>

using namespace RadarDisplay;

static const int PAUSABLE = 1;
static const int RUNABLE = 2;

static const char PLAY_ICON[] = ":/icons/media-playback-start.png";
static const char PAUSE_ICON[] = ":/icons/media-playback-pause.png";
static const char CLEAR_ICON[] = ":/icons/edit-clear.png";
static const char CONFIGURE_ICON[] = ":/icons/configure.png";

PlotWatchControl::PlotWatchControl(PlotWatchManager *pm, QWidget *parent) :
    QWidget(parent),
    m_pm(pm)
{
    m_pauseResumeAction = new QAction(QIcon(PAUSE_ICON), QString(), this);
    m_pauseResumeAction->setData(QVariant(PAUSABLE));
    connect(m_pauseResumeAction, SIGNAL(triggered()), SLOT(plotWatchPauseResume()));

    m_clearAction = new QAction(QIcon(CLEAR_ICON), QString(), this);
    connect(m_clearAction, SIGNAL(triggered()), SLOT(plotWatchClear()));

    m_configAction = new QAction(QIcon(CONFIGURE_ICON), QString(), this);
    connect(m_configAction, SIGNAL(triggered()), SLOT(plotWatchConfig()));


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    QToolButton *pauseButton = new QToolButton(this);
    pauseButton->setDefaultAction(m_pauseResumeAction);
    pauseButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    layout->addWidget(pauseButton);

    QToolButton *clearButton = new QToolButton(this);
    clearButton->setDefaultAction(m_clearAction);
    clearButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    layout->addWidget(clearButton);

    QToolButton *configButton = new QToolButton(this);
    configButton->setDefaultAction(m_configAction);
    configButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    layout->addWidget(configButton);

    connect(m_pm, SIGNAL(currentPlotWatchChanged(IPlotWatch*)),
            SLOT(currentPlotWatchChanged(IPlotWatch*)));
}

PlotWatchControl::~PlotWatchControl()
{
}

void PlotWatchControl::currentPlotWatchChanged(IPlotWatch *watch)
{
    if (!watch) {
        m_pauseResumeAction->setEnabled(false);
        m_clearAction->setEnabled(false);
        m_configAction->setEnabled(false);
        return;
    }
    m_pauseResumeAction->setEnabled(watch->abilities() & IPlotWatch::PauseResumeAbility);
    m_clearAction->setEnabled(watch->abilities() & IPlotWatch::ClearAbility);
    m_configAction->setEnabled(watch->abilities() & IPlotWatch::ConfigAbility);

    if (watch->state() == IPlotWatch::Running) {
        m_pauseResumeAction->setIcon(QIcon(PAUSE_ICON));
        m_pauseResumeAction->setData(QVariant(PAUSABLE));
    } else if (watch->state() == IPlotWatch::Paused) {
        m_pauseResumeAction->setIcon(QIcon(PLAY_ICON));
        m_pauseResumeAction->setData(QVariant(RUNABLE));
    } else {
        Q_ASSERT(0);
    }
}

void PlotWatchControl::plotWatchPauseResume()
{
    IPlotWatch *watch = m_pm->currentPlotWatch();
    if (!watch)
        return;
    int state = m_pauseResumeAction->data().value<int>();
    if (state == PAUSABLE) {
        watch->pause();
        m_pauseResumeAction->setIcon(QIcon(PLAY_ICON));
        m_pauseResumeAction->setData(QVariant(RUNABLE));
    } else if (state == RUNABLE) {
        watch->resume();
        m_pauseResumeAction->setIcon(QIcon(PAUSE_ICON));
        m_pauseResumeAction->setData(QVariant(PAUSABLE));
    } else {
        Q_ASSERT(0);
    }
}

void PlotWatchControl::plotWatchClear()
{
    IPlotWatch *watch = m_pm->currentPlotWatch();
    if (!watch)
        return;
    watch->clear();
}

void PlotWatchControl::plotWatchConfig()
{
    IPlotWatch *watch = m_pm->currentPlotWatch();
    if (!watch)
        return;
    watch->config();
}
