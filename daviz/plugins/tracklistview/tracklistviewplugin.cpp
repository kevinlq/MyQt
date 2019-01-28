#include "tracklistviewplugin.h"
#include "tracklistmodel.h"
#include "tracklistview.h"
#include "core/panelwidget.h"
#include "core/coreconstant.h"
#include "core/icore.h"
#include "core/iradar.h"
#include <QtPlugin>
#include <QTranslator>
#include <QApplication>

using namespace RadarDisplay;
using namespace ExtensionSystem;

TrackListViewPlugin::TrackListViewPlugin() :
    ExtensionSystem::IPlugin()
{
}


bool TrackListViewPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)
    QTranslator *translator = new QTranslator(this);
    translator->load(QLocale::system(), "TrackListView", ".", ":/translations");
    qApp->installTranslator(translator);
    return true;
}

void TrackListViewPlugin::extensionsInitialized()
{
    m_trackListModel = new TrackListModel(this);
    m_trackListView = new TrackListView;
    m_trackListView->setModel(m_trackListModel);
    m_panel = new PanelWidget(m_trackListView, tr("Track List"), TRACK_PANEL_PRIORITY);
    addObject(m_panel);

    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(currentRadarChanged(IRadar*)));
}

IPlugin::ShutdownFlag TrackListViewPlugin::aboutToShutdown()
{
    removeObject(m_panel);
    return IPlugin::SynchronousShutdown;
}

void TrackListViewPlugin::currentRadarChanged(IRadar *radar)
{
    m_trackListModel->setRadar(radar);
}

Q_EXPORT_PLUGIN(TrackListViewPlugin)
