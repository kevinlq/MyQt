#include "mainwindow.h"
#include "iradar.h"
#include "icore.h"
#include "iview.h"
#include "panelgroup.h"
#include "viewgroup.h"
#include "extensionsystem/pluginmanager.h"
#include "plugindialog.h"
#include "versiondialog.h"
#include "menumanager.h"
#include "coreconstant.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QTimer>
#include <QApplication>
#include <QStatusBar>
#include <QMessageBox>

using namespace ExtensionSystem;
using namespace RadarDisplay;

static MainWindow *g_mainWindow = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_radar(0),
    m_panelGroup(0),
    m_mainMenu(0)
{
//    m_radar = new TestRadar;
//    m_radar = new QSRadar;
    m_viewGroup = new ViewGroup(this);
    m_panelGroup = new PanelGroup(this);
    QWidget *w = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(w);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_viewGroup);
    layout->addWidget(m_panelGroup, 1);
    setCentralWidget(w);

    m_menuManager = new MenuManager(this);
    createMenus();

    statusBar()->hide();

    connect(ICore::instance(), SIGNAL(currentViewChanged(IView*)), SLOT(setView(IView*)));
}

void MainWindow::createMenus()
{
    m_menuManager->addMenu(HELP_MENU_NAME, HELP_MENU_PRIORITY);

    QAction *aboutMeAction = new QAction(tr("About Daviz..."), this);
    connect(aboutMeAction, SIGNAL(triggered()), SLOT(aboutMe()));
    m_menuManager->addAction(HELP_MENU_NAME, aboutMeAction);

    QAction *aboutPluginsAction = new QAction(tr("About plugins..."), this);
    connect(aboutPluginsAction, SIGNAL(triggered()), SLOT(aboutPlugins()));
    m_menuManager->addAction(HELP_MENU_NAME, aboutPluginsAction);
}

MainWindow::~MainWindow()
{
}

MainWindow *MainWindow::instance()
{
    if (!g_mainWindow) {
        ICore::instance();
        g_mainWindow = new MainWindow;
    }
    return g_mainWindow;
}

ViewGroup *MainWindow::viewGroup()
{
    return instance()->m_viewGroup;
}

PanelGroup *MainWindow::panelGroup()
{
    return instance()->m_panelGroup;
}

MenuManager *MainWindow::menuManager()
{
    return instance()->m_menuManager;
}

void MainWindow::setView(IView *view)
{
    viewGroup()->setView(view);
}

void MainWindow::aboutMe()
{
    VersionDialog v(this);
    v.exec();
}

void MainWindow::aboutPlugins()
{
    PluginDialog p(this);
    p.exec();
}

void MainWindow::execMainMenu()
{
    if (!m_mainMenu)
        m_mainMenu = m_menuManager->createMenu();
    m_mainMenu->exec(QCursor::pos());
}
