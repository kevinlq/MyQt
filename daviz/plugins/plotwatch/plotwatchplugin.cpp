#include "plotwatchplugin.h"
#include "iplotwatch.h"
#include "plotwatchmanager.h"
#include "core/coreconstant.h"
#include "core/icore.h"
#include "core/panelwidget.h"
#include <QtPlugin>
#include <QTranslator>
#include <QLocale>
#include <QApplication>

using namespace ExtensionSystem;
using namespace RadarDisplay;

PlotWatchPlugin::PlotWatchPlugin() :
    IPlugin()
{
}

bool PlotWatchPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *translator = new QTranslator(this);
    translator->load(QLocale::system(), "PlotWatch", ".", ":/translations");
    qApp->installTranslator(translator);
    return true;
}

void PlotWatchPlugin::extensionsInitialized()
{
    m_pm = new PlotWatchManager;
    addObject(m_pm);

    m_panel = new PanelWidget(m_pm, tr("Plot Watch"), PLOT_PANEL_PRIORITY);
    addObject(m_panel);

    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)),
            SLOT(currentRadarChanged(IRadar*)));
}

IPlugin::ShutdownFlag PlotWatchPlugin::aboutToShutdown()
{
    removeObject(m_pm);
    removeObject(m_panel);
    return IPlugin::SynchronousShutdown;
}

void PlotWatchPlugin::currentRadarChanged(IRadar *radar)
{
    m_pm->setRadar(radar);
}

Q_EXPORT_PLUGIN(PlotWatchPlugin)
