#ifndef PLOTWATCHPLUGIN_H
#define PLOTWATCHPLUGIN_H

#include "plotwatch_global.h"
#include "extensionsystem/iplugin.h"

namespace RadarDisplay {
class IRadar;
class PlotWatchManager;
class PanelWidget;
class PLOTWATCH_EXPORT PlotWatchPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "PlotWatch.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    explicit PlotWatchPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ExtensionSystem::IPlugin::ShutdownFlag aboutToShutdown();
    
signals:
    
public slots:
    void currentRadarChanged(IRadar *radar);

private:
    RadarDisplay::PlotWatchManager *m_pm;
    PanelWidget *m_panel;
};
}
#endif // PLOTWATCHPLUGIN_H
