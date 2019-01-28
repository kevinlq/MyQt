#include "ppiviewplugin.h"
#include "ppiview.h"
#include "ppicontrol.h"
#include "core/panelwidget.h"
#include "core/coreconstant.h"
#include "core/mainwindow.h"
#include "extensionsystem/pluginmanager.h"
#include <QtPlugin>
#include <QDebug>
#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>

using namespace ExtensionSystem;
using namespace RadarDisplay;

PPIViewPlugin::PPIViewPlugin() :
    ExtensionSystem::IPlugin()
{
}

bool PPIViewPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *t = new QTranslator(this);
    t->load(QLocale::system(), "PPIView", ".", ":/translations");
    qApp->installTranslator(t);
    return true;
}

void PPIViewPlugin::extensionsInitialized()
{
    m_ppiView = new PPIView(MainWindow::instance());
    addObject(m_ppiView);

    m_ppiControl = new PPIControl(m_ppiView);
    m_ppiControlPanel = new PanelWidget(m_ppiControl, tr("PPI Control"), VIEW_PANEL_PRIORITY);
    m_ppiControlPanel->setViewContext(m_ppiView);
    addObject(m_ppiControlPanel);
}

IPlugin::ShutdownFlag PPIViewPlugin::aboutToShutdown()
{
    removeObject(m_ppiView);
    removeObject(m_ppiControlPanel);
    return IPlugin::SynchronousShutdown;
}

Q_EXPORT_PLUGIN(PPIViewPlugin)
