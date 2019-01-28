#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include "extensionsystem/iplugin.h"
#include "core_global.h"
#include <QList>

class QAction;
namespace RadarDisplay {
class ICore;
class MainWindow;
class IRadar;
class IView;
class PanelWidget;
class CORE_EXPORT CorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.BlueBlazer.Daviz.Plugin" FILE "Core.json")
    Q_INTERFACES(ExtensionSystem::IPlugin)
public:
    explicit CorePlugin();
    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();
    
signals:
    
public slots:
    void aboutToRemoveObject(QObject *object);
    void changeRadar();

private:
    ICore *m_core;
    MainWindow *m_mainWindow;
    QList<QAction *> m_radarActions;
    QList<IRadar *> m_radars;
    QList<IView *> m_views;
    QList<PanelWidget *> m_panels;
};
}

#endif // COREPLUGIN_H
