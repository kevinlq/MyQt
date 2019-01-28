#ifndef ICORE_H
#define ICORE_H

#include "core_global.h"
#include "plotdata.h"
#include "trackdata.h"
#include "targetdata.h"
#include <QObject>
#include <QSettings>

namespace RadarDisplay {
class IRadar;
class IView;
class RadarGroup;
class ViewGroup;
class PanelGroup;
class CORE_EXPORT ICore : public QObject
{
    Q_OBJECT
public:
    static ICore *instance();
    static IRadar *currentRadar();
    static void setCurrentRadar(IRadar *radar);
    static RadarGroup *radarGroup();

    static IView *currentView();
    static void setCurrentView(IView *view);
    static ViewGroup *viewGroup();

    static PanelGroup *panelGroup();

    static QSettings *settings(QSettings::Scope scope = QSettings::UserScope);

signals:
    void currentRadarAboutToChange(IRadar *);
    void currentRadarChanged(IRadar *);
    void currentViewAboutToChange(IView *);
    void currentViewChanged(IView *);
    
public slots:

private:
    explicit ICore(QObject *parent = 0);
    IRadar *m_radar;
    IView *m_view;
    RadarGroup *m_radarGroup;
};
}
#endif // ICORE_H
