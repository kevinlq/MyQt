#ifndef PPIVIEWPLUGIN_H
#define PPIVIEWPLUGIN_H

#include "extensionsystem/iplugin.h"
#include "ppiview_global.h"

namespace RadarDisplay {
class PPIView;
class PPIControl;
class PanelWidget;
}

class PPIVIEW_EXPORT PPIViewPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "PPIView.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    PPIViewPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();
    
signals:
    
public slots:
    
private:
    RadarDisplay::PPIView *m_ppiView;
    RadarDisplay::PPIControl *m_ppiControl;
    RadarDisplay::PanelWidget *m_ppiControlPanel;
};

#endif // PPIVIEWPLUGIN_H
