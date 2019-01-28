#ifndef QSRADARPLUGIN_H
#define QSRADARPLUGIN_H

#include "extensionsystem/iplugin.h"
#include "replay_global.h"

namespace RadarDisplay {
class IRadar;
class Recorder;
class ReplayRadar;
class REPLAY_EXPORT ReplayPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "Replay.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    ReplayPlugin();
    ~ReplayPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    void makeReplayDir();
    
signals:
    
public slots:
    
private:
    Recorder *m_recorder;
    ReplayRadar *m_replayRadar;
};
}

#endif // QSRADARPLUGIN_H
