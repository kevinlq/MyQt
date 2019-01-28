#ifndef PANELGROUP_H
#define PANELGROUP_H

#include "core_global.h"
#include <QSplitter>

namespace RadarDisplay {
class PanelWidget;
class IView;
class IRadar;
class CORE_EXPORT PanelGroup : public QSplitter
{
    Q_OBJECT
public:
    explicit PanelGroup(QWidget *parent = 0);
    PanelWidget *addPanel(QWidget *_widget, const QString &text, int priority);
    PanelWidget *addPanel(PanelWidget *panel);
    void removePanel(PanelWidget *panel);
    
signals:
    
public slots:
    void adjustPanelVisbility();
    
};
}
#endif // PANELGROUP_H
