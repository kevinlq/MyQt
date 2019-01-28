#ifndef TRACKLISTVIEWPLUGIN_H
#define TRACKLISTVIEWPLUGIN_H

#include "tracklistview_global.h"
#include "extensionsystem/iplugin.h"

namespace RadarDisplay {
class TrackListModel;
class TrackListView;
class PanelWidget;
class IRadar;
class TRACKLISTVIEW_EXPORT TrackListViewPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "TrackListView.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    explicit TrackListViewPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ExtensionSystem::IPlugin::ShutdownFlag aboutToShutdown();
    
signals:
    
public slots:
    void currentRadarChanged(IRadar *radar);
    
private:
    TrackListModel *m_trackListModel;
    TrackListView *m_trackListView;
    PanelWidget *m_panel;
};
}
#endif // TRACKLISTVIEWPLUGIN_H
