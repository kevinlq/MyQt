#ifndef VIEWCONTROL_H
#define VIEWCONTROL_H

#include "iradar.h"
#include "iview.h"
#include <QWidget>
#include <QList>
#include <QToolButton>

namespace RadarDisplay {
class RangeBar;
class ViewControl : public QWidget
{
    Q_OBJECT
public:
    explicit ViewControl(QWidget *parent = 0);
    
signals:
    
public slots:
    void viewButtonClicked();
    void plotLayerButtonClicked();
    void trackLayerButtonClicked();
    void rangeButtonClicked();
    void currentRadarChanged(IRadar *newRadar);
    void currentViewAboutToChange(IView *newView);
    void currentViewChanged(IView *newView);
    void currentViewSelectionChanged(const IView::Selection &sel);
    void currentViewLayersChanged(const IView::Layers &layers);

private:
    QList<QToolButton *> m_viewButtons;
    QToolButton *m_plotButton;
    QToolButton *m_trackButton;
    QToolButton *m_rangeButton;
    IView::Selection m_lastSelection;
};
}
#endif // VIEWCONTROL_H
