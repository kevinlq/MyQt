#ifndef PPICONTROL_H
#define PPICONTROL_H

#include <QWidget>
#include <QPointF>
#include <QEvent>

class QToolBar;
class QAction;
class QWheelEvent;

namespace RadarDisplay {
class PPIView;
class PPIControl : public QWidget
{
    Q_OBJECT
public:
    explicit PPIControl(PPIView *ppi, QWidget *parent = 0);
    ~PPIControl();
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
    void resetView();
    void updatePositionText();
    void updateTimeText();
    void updateTransformText();
    void updateTexts();

private:
    void carteToPolar(qreal x, qreal y, qreal &r, qreal &a);

    PPIView *m_view;
    QPointF m_origin;
    float m_scale;
    bool m_reportMousePosition;
};
}
#endif // PPIVIEWTOOLBOX_H
