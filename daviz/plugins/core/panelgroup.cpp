#include "panelgroup.h"
#include "panelwidget.h"
#include "icore.h"
#include <QLayout>
#include <QDebug>

using namespace RadarDisplay;

PanelGroup::PanelGroup(QWidget *parent) :
    QSplitter(Qt::Vertical, parent)
{
    setChildrenCollapsible(false);
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    addWidget(spacer);
    setStretchFactor(indexOf(spacer), 1);

    connect(ICore::instance(), SIGNAL(currentViewChanged(IView*)), SLOT(adjustPanelVisbility()));
    connect(ICore::instance(), SIGNAL(currentRadarChanged(IRadar*)), SLOT(adjustPanelVisbility()));
}

PanelWidget *PanelGroup::addPanel(QWidget *_widget, const QString &text, int priority)
{
    PanelWidget *panel = new PanelWidget(_widget, text, priority);
    int insertIndex = count() - 1;
    for (int i = 0; i < count() - 1; i++) {
        PanelWidget *pw = qobject_cast<PanelWidget *>(widget(i));
        if (pw->priority() > panel->priority()) {
            insertIndex = i;
            break;
        }
    }
    insertWidget(insertIndex, panel);
    return panel;
}

PanelWidget *PanelGroup::addPanel(PanelWidget *panel)
{
    if (indexOf(panel) != -1)
        return panel;
    int insertIndex = count() - 1;
    for (int i = 0; i < count() - 1; i++) {
        PanelWidget *pw = qobject_cast<PanelWidget *>(widget(i));
        if (pw->priority() > panel->priority()) {
            insertIndex = i;
            break;
        }
    }
    insertWidget(insertIndex, panel);
    return panel;
}

void PanelGroup::removePanel(PanelWidget *panel)
{
    panel->hide();
    panel->setParent(0);
}

void PanelGroup::adjustPanelVisbility()
{
    for (int i = 0; i < count() - 1; i++) {
        PanelWidget *panel = qobject_cast<PanelWidget *>(widget(i));
        bool enable;
        if (panel->viewContext() && panel->viewContext() != ICore::currentView())
            enable = false;
        else if (panel->radarContext() && panel->radarContext() != ICore::currentRadar())
            enable = false;
        else
            enable = true;
        panel->setVisible(enable);
    }
}
