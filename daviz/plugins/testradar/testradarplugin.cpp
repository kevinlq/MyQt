#include "testradarplugin.h"
#include "testradar.h"
#include <QtPlugin>
#include <QLocale>
#include <QTranslator>
#include <QCoreApplication>
using namespace RadarDisplay;
using namespace ExtensionSystem;

TestRadarPlugin::TestRadarPlugin() :
    IPlugin(),
    m_radar(0)
{
}

bool RadarDisplay::TestRadarPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *t = new QTranslator(this);
    t->load(QLocale::system(), "TestRadar", ".", ":/translations");
    qApp->installTranslator(t);
    return true;
}

void TestRadarPlugin::extensionsInitialized()
{
    m_radar = new TestRadar(this);
    addObject(m_radar);
}

IPlugin::ShutdownFlag TestRadarPlugin::aboutToShutdown()
{
    removeObject(m_radar);
    return IPlugin::SynchronousShutdown;
}

Q_EXPORT_PLUGIN(TestRadarPlugin)
