#include "replayplugin.h"
#include "recorder.h"
#include "replayradar.h"
#include "recordreplaywidget.h"
#include "replayconstants.h"
#include "coreconstant.h"
#include <extensionsystem/pluginmanager.h>
#include <icore.h>
#include <panelwidget.h>
#include <panelgroup.h>
#include <QtPlugin>
#include <QDebug>
#include <QTranslator>
#include <QCoreApplication>
#include <QDir>

using namespace ExtensionSystem;
using namespace RadarDisplay;

ReplayPlugin::ReplayPlugin() :
    ExtensionSystem::IPlugin()
{
}

ReplayPlugin::~ReplayPlugin()
{
}

bool ReplayPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *t = new QTranslator(this);
    t->load(QLocale::system(), "Replay", ".", ":/translations");
    qApp->installTranslator(t);

    makeReplayDir();

    m_recorder = new Recorder;
    addAutoReleasedObject(m_recorder);
    m_replayRadar = new ReplayRadar;
    addAutoReleasedObject(m_replayRadar);

    RecordReplayWidget *w = new RecordReplayWidget(m_recorder, m_replayRadar);
    PanelWidget *pw = new PanelWidget(w, tr("Record & Replay"), REPLAY_PANEL_PRIORITY);
    addAutoReleasedObject(pw);

    return true;
}

void ReplayPlugin::extensionsInitialized()
{
}

IPlugin::ShutdownFlag ReplayPlugin::aboutToShutdown()
{
    return IPlugin::SynchronousShutdown;
}

void ReplayPlugin::makeReplayDir()
{
    QDir dir = QDir(qApp->applicationDirPath());
    dir.mkdir(REPLAY_DIR_NAME);
}

Q_EXPORT_PLUGIN(ReplayPlugin)
