#include "coreplugin.h"
#include "mainwindow.h"
#include "panelgroup.h"
#include "radargroup.h"
#include "viewgroup.h"
#include "viewcontrol.h"
#include "iradar.h"
#include "iview.h"
#include "panelwidget.h"
#include "icore.h"
#include "menumanager.h"
#include "coreconstant.h"
#include "extensionsystem/pluginmanager.h"
#include <QtPlugin>
#include <QAction>
#include <QActionGroup>
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QPixmapCache>
#include <QIcon>
#include <QFile>
#include <QVariant>
#include <QTranslator>

using namespace RadarDisplay;
using namespace ExtensionSystem;

CorePlugin::CorePlugin() :
    ExtensionSystem::IPlugin()
{
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    QTranslator *translator = new QTranslator(this);
    translator->load(QLocale::system(), "Core", ".", ":/translations");
    qApp->installTranslator(translator);

    QPixmapCache::setCacheLimit(200*1024);

    /*
    QFile file(":/styles/dark.css");
    file.open(QIODevice::ReadOnly);
    QString styleSheet(file.readAll());
    qApp->setStyleSheet(styleSheet);
    */

    m_core = ICore::instance();
    m_mainWindow = MainWindow::instance();

    connect(PluginManager::instance(), SIGNAL(aboutToRemoveObject(QObject*)),
            SLOT(aboutToRemoveObject(QObject*)));
    return true;
}

void CorePlugin::extensionsInitialized()
{
    m_radars = PluginManager::getObjects<IRadar>();
    MainWindow::menuManager()->addMenu(RADAR_MENU_NAME, RADAR_MENU_PRIORITY);
    QActionGroup *radarActionGroup = new QActionGroup(m_mainWindow);
    QAction *defaultRadarAction = 0;
    foreach (IRadar *radar, m_radars) {
        m_core->radarGroup()->addRadar(radar);
        if (!radar->isUserVisible())
            continue;
        QAction *action = new QAction(radar->name(), m_mainWindow);
        action->setCheckable(true);
        action->setData(QVariant::fromValue<IRadar *>(radar));
        m_radarActions.append(action);
        radarActionGroup->addAction(action);
        defaultRadarAction = action;
        connect(action, SIGNAL(triggered()), SLOT(changeRadar()));
        MainWindow::menuManager()->addAction(RADAR_MENU_NAME, action);
    }

    m_views = PluginManager::getObjects<IView>();
    foreach (IView *view, m_views)
        m_core->viewGroup()->addView(view);

    ViewControl *viewControl = new ViewControl;
    PanelWidget *viewPanel = new PanelWidget(viewControl, tr("View control"), VIEW_PANEL_PRIORITY);
    addAutoReleasedObject(viewPanel);

    m_panels = PluginManager::getObjects<PanelWidget>();
    foreach (PanelWidget *panel, m_panels)
        m_core->panelGroup()->addPanel(panel);

    if (defaultRadarAction) {
        defaultRadarAction->setChecked(true);
        m_core->setCurrentRadar(defaultRadarAction->data().value<IRadar *>());
    }
    if (!m_views.empty())
        m_core->setCurrentView(m_views.first());

    m_mainWindow->setMenuBar(m_mainWindow->menuManager()->createMenuBar());
    m_mainWindow->showMaximized();
}

IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
    ICore *core = ICore::instance();
    foreach (IRadar *radar, m_radars)
        core->radarGroup()->removeRadar(radar);
    m_radars.clear();
    foreach (IView *view, m_views)
        core->viewGroup()->removeView(view);
    m_views.clear();
    foreach (PanelWidget *panel, m_panels)
        core->panelGroup()->removePanel(panel);
    m_panels.clear();
    delete m_mainWindow;
    return IPlugin::SynchronousShutdown;
}

void CorePlugin::aboutToRemoveObject(QObject *object)
{
    IRadar *radar = qobject_cast<IRadar *>(object);
    if (radar && m_radars.contains(radar)) {
        m_radars.removeOne(radar);
        ICore::instance()->radarGroup()->removeRadar(radar);
        return;
    }

    IView *view = qobject_cast<IView *>(object);
    if (view && m_views.contains(view)) {
        m_views.removeOne(view);
        ICore::instance()->viewGroup()->removeView(view);
        return;
    }

    PanelWidget *panel = qobject_cast<PanelWidget *>(object);
    if (panel && m_panels.contains(panel)) {
        m_panels.removeOne(panel);
        ICore::instance()->panelGroup()->removePanel(panel);
        return;
    }
}

void CorePlugin::changeRadar()
{
    QAction *action = qobject_cast<QAction *>(sender());
    IRadar *radar = action->data().value<IRadar *>();
    ICore::setCurrentRadar(radar);
}

Q_EXPORT_PLUGIN(CorePlugin)
