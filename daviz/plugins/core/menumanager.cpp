#include "menumanager.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>

using namespace RadarDisplay;

MenuManager::MenuManager(QObject *parent) :
    QObject(parent)
{
}

void MenuManager::addMenu(const QString &catalog, int priority)
{
    if (m_catalogs.contains(catalog))
        return;
    m_priorityMap.insert(catalog, priority);
    if (m_catalogs.isEmpty())
        m_catalogs.append(catalog);
    else {
        int index = 0;
        while (m_priorityMap.value(m_catalogs[index]) <= priority)
            index++;
        m_catalogs.insert(index, catalog);
    }
}

void MenuManager::addAction(const QString &catalog, QAction *action)
{
    if (!m_catalogs.contains(catalog))
        return;
    QList<QAction *> actionList = m_actionListMap.value(catalog);
    if (actionList.contains(action))
        return;
    actionList.append(action);
    m_actionListMap.insert(catalog, actionList);
}

void MenuManager::addOperator(const QString &catalog)
{
    addAction(catalog, 0);
}

QMenuBar *MenuManager::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar;
    foreach (const QString &catalog, m_catalogs) {
        QMenu *menu = menuBar->addMenu(qApp->translate("Menu", catalog.toUtf8()));
        foreach (QAction *action, m_actionListMap.value(catalog)) {
            if (action)
                menu->addAction(action);
            else
                menu->addSeparator();
        }
    }
    return menuBar;
}

QMenu *MenuManager::createMenu()
{
    QMenu *rootMenu = new QMenu;
    foreach (const QString &catalog, m_catalogs) {
        QMenu *menu = rootMenu->addMenu(qApp->translate("Menu", catalog.toUtf8()));
        foreach (QAction *action, m_actionListMap.value(catalog)) {
            if (action)
                menu->addAction(action);
            else
                menu->addSeparator();
        }
    }
    return rootMenu;
}
