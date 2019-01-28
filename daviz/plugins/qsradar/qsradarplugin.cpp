#include "qsradarplugin.h"
#include "extensionsystem/pluginmanager.h"
#include "qsradar.h"
#include <QtPlugin>
#include <QDebug>
#include <QTranslator>
#include <QCoreApplication>

using namespace ExtensionSystem;
using namespace RadarDisplay;

QSRadarPlugin::QSRadarPlugin() :
    ExtensionSystem::IPlugin()
{
}

bool QSRadarPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *t = new QTranslator(this);
    t->load(QLocale::system(), "QSRadar", ".", ":/translations");
    qApp->installTranslator(t);
    m_radar = new QSRadar;
    return true;
}

void QSRadarPlugin::extensionsInitialized()
{
    addObject(m_radar);
}

IPlugin::ShutdownFlag QSRadarPlugin::aboutToShutdown()
{
    removeObject(m_radar);
    return IPlugin::SynchronousShutdown;
}

Q_EXPORT_PLUGIN(QSRadarPlugin)
