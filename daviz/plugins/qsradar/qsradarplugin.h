#ifndef QSRADARPLUGIN_H
#define QSRADARPLUGIN_H

#include "extensionsystem/iplugin.h"
#include "qsradar_global.h"

class QSRadar;

namespace RadarDisplay {
class QSRADAR_EXPORT QSRadarPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "QSRadar.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    QSRadarPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();
    
signals:
    
public slots:
    
private:
    QSRadar *m_radar;
};
}

#endif // QSRADARPLUGIN_H
