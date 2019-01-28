#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core_global.h"
#include <QMainWindow>

class QMenu;
namespace RadarDisplay {
class IRadar;
class PPIViewer;
class PanelGroup;
class RadarGroup;
class ViewGroup;
class IView;
class MenuManager;
class CORE_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    ~MainWindow();

    static MainWindow *instance();
    static ViewGroup *viewGroup();
    static PanelGroup *panelGroup();
    static MenuManager *menuManager();

public slots:
    static void setView(IView *view);

    void aboutMe();
    void aboutPlugins();
    void execMainMenu();
    
private:
    explicit MainWindow(QWidget *parent = 0);
    void createMenus();

    IRadar *m_radar;
    ViewGroup *m_viewGroup;
    PanelGroup *m_panelGroup;
    RadarGroup *m_radarGroup;
    MenuManager *m_menuManager;
    QMenu *m_mainMenu;
};
}
#endif // MAINWINDOW_H
