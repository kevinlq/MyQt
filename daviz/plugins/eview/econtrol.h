#ifndef ECONTROL_H
#define ECONTROL_H

#include <QWidget>
#include <QPointF>
#include <QEvent>

class QToolBar;
class QAction;
class QWheelEvent;

namespace RadarDisplay {
class IView;
class EView;
class EControl : public QObject
{
    Q_OBJECT
public:
    explicit EControl(EView *view, QObject *parent = 0);
    ~EControl();
    void createActions();
    bool eventFilter(QObject *object, QEvent *event);
    bool wheelEventFilter(QWheelEvent *event);
    bool mouseEventFilter(QMouseEvent *event);
    bool keyEventFilter(QKeyEvent *event);
    bool enterEventFilter(QEvent *);
    bool leaveEventFilter(QEvent *);
    void timerEvent(QTimerEvent *);
signals:
    
public slots:
//    void currentViewChanged(IView *view);
    void resetView();
    void updatePositionText();
    void updateTimeText();
    void updateTransformText();
    void updateTexts();

private:
    /*
    bool inPanel() const;
    void setPanelVisible(bool enable);
    */

    EView *m_view;
    QPointF m_origin;
    float m_scale;
    bool m_reportMousePosition;
};
}
#endif // ECONTROL_H
