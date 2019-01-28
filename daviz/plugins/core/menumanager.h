#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "core_global.h"
#include <QObject>
#include <QList>
#include <QMap>
#include <QString>

class QAction;
class QMenuBar;
class QMenu;
namespace RadarDisplay {
class CORE_EXPORT MenuManager : public QObject
{
    Q_OBJECT
public:
    explicit MenuManager(QObject *parent = 0);
    void addMenu(const QString &catalog, int priority);
    void addAction(const QString &catalog, QAction *action);
    void addOperator(const QString &catalog);
    QMenuBar *createMenuBar();
    QMenu *createMenu();
    
signals:
    
public slots:
    
private:
    QMap<QString, int> m_priorityMap;
    QList<QString> m_catalogs;
    QMap<QString, QList<QAction *> > m_actionListMap;
};
}
#endif // MENUMANAGER_H
