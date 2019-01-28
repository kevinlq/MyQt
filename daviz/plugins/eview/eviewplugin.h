#ifndef EVIEWPLUGIN_H
#define EVIEWPLUGIN_H

#include "extensionsystem/iplugin.h"
#include "eview_global.h"

namespace RadarDisplay {
class EView;
class EControl;
}

class EVIEW_EXPORT EViewPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "EView.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    EViewPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();
    
signals:
    
public slots:
    
private:
    RadarDisplay::EView *m_eView;
    RadarDisplay::EControl *m_eControl;
};

#endif // EVIEWPLUGIN_H
