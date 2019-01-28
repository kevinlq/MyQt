#include "eviewplugin.h"
#include "eview.h"
#include "econtrol.h"
#include "extensionsystem/pluginmanager.h"
#include "core/panelwidget.h"
#include "core/coreconstant.h"
#include "core/mainwindow.h"
#include <QtPlugin>
#include <QDebug>
#include <QCoreApplication>
#include <QTranslator>
#include <QLocale>

using namespace ExtensionSystem;
using namespace RadarDisplay;

EViewPlugin::EViewPlugin() :
    ExtensionSystem::IPlugin()
{
}

bool EViewPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *t = new QTranslator(this);
    t->load(QLocale::system(), "EView", ".", ":/translations");
    qApp->installTranslator(t);
    return true;
}

void EViewPlugin::extensionsInitialized()
{
    m_eView = new EView(MainWindow::instance());
    addObject(m_eView);

    m_eControl = new EControl(m_eView, this);
}

IPlugin::ShutdownFlag EViewPlugin::aboutToShutdown()
{
    removeObject(m_eView);
    return IPlugin::SynchronousShutdown;
}

Q_EXPORT_PLUGIN(EViewPlugin)
