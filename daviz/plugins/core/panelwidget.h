#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include "core_global.h"
#include <QWidget>
#include <QString>

class QAction;
class QPushButton;
class QToolBar;
class QToolButton;
class QSplitter;
class QLabel;
class QPropertyAnimation;

namespace RadarDisplay {
class PanelTitleBar;
class IView;
class IRadar;
class CORE_EXPORT PanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PanelWidget(QSplitter *parent = 0);
    explicit PanelWidget(QWidget *widget, const QString &text, int priority, QSplitter *parent = 0);
    ~PanelWidget();
    QWidget *widget() const;
    void setWidget(QWidget *w);
    QString text() const;
    void setText(const QString &t);
    int priority() const;
    void setPriority(int prio);
    void adjustSize(int contentHeight);

    IView *viewContext() const;
    void setViewContext(IView *view);

    IRadar *radarContext() const;
    void setRadarContext(IRadar *radar);

    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    
signals:
    void priorityChanged(int prio);
    
public slots:
    void toggleExpansion(bool toggle);
    
private:
    void init();
    QWidget *m_widget;
    QString m_title;
    int m_priority;
    PanelTitleBar *m_titleBar;
    int m_foldedHeight;
    int m_expandedHeight;
    int m_expandedMaximumHeight;
    IView *m_viewContext;
    IRadar *m_radarContext;
};
}
#endif // PANELWIDGET_H
