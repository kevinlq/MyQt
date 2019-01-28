#ifndef TESTRADARPLUGIN_H
#define TESTRADARPLUGIN_H

#include "testradar_global.h"
#include "extensionsystem/iplugin.h"

namespace RadarDisplay {
class TestRadar;
class TESTRADAR_EXPORT TestRadarPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "TestRadar.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    TestRadarPlugin();
    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ExtensionSystem::IPlugin::ShutdownFlag aboutToShutdown();

private:
    TestRadar *m_radar;
};
}

#endif // TESTRADARPLUGIN_H
