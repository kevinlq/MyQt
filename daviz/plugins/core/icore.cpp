#include "icore.h"
#include "iradar.h"
#include "iview.h"
#include "radargroup.h"
#include "viewgroup.h"
#include "mainwindow.h"
#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;
using namespace RadarDisplay;

static ICore *g_core = 0;

ICore::ICore(QObject *parent) :
    QObject(parent),
    m_radar(0),
    m_view(0),
    m_radarGroup(new RadarGroup(this))
{
}

ICore *ICore::instance()
{
    if (!g_core) {
        g_core = new ICore;
        MainWindow::instance();
    }
    return g_core;
}

IRadar *ICore::currentRadar()
{
    return instance()->m_radar;
}

void ICore::setCurrentRadar(IRadar *radar)
{
    if (!g_core)
        g_core = instance();
    if (g_core->m_radar != radar) {
        emit g_core->currentRadarAboutToChange(g_core->m_radar);
        if (g_core->m_radar)
            g_core->m_radar->deactive();
        g_core->m_radar = radar;
        if (radar)
            radar->active();
        emit g_core->currentRadarChanged(radar);

        foreach (IView *view, viewGroup()->viewList()) {
            view->setRadar(radar);
        }
    }
}

RadarGroup *ICore::radarGroup()
{
    return instance()->m_radarGroup;
}

IView *ICore::currentView()
{
    return instance()->m_view;
}

void ICore::setCurrentView(IView *view)
{
    if (!g_core)
        g_core = instance();
    if (g_core->m_view != view) {
        emit g_core->currentViewAboutToChange(g_core->m_view);
        if (g_core->m_view)
            g_core->m_view->deactive();
        g_core->m_view = view;
        if (view)
            view->active();
        emit g_core->currentViewChanged(view);
    }
}

ViewGroup *ICore::viewGroup()
{
    return MainWindow::instance()->viewGroup();
}

PanelGroup *ICore::panelGroup()
{
    return MainWindow::instance()->panelGroup();
}

QSettings *ICore::settings(QSettings::Scope scope)
{
    if (scope == QSettings::UserScope)
        return PluginManager::settings();
    else
        return PluginManager::globalSettings();
}
