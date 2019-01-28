#ifndef RANGEBAR_H
#define RANGEBAR_H

#include "utils_global.h"
#include <QWidget>

class QPainter;
namespace RadarDisplay {
class UTILS_EXPORT RangeBar : public QWidget
{
    Q_OBJECT
public:
    explicit RangeBar(Qt::Orientation orient, qreal min, qreal max, QWidget *parent = 0);

    qreal rangeMin() const;
    qreal rangeMax() const;
    void setRangeBound(qreal min, qreal max);

    QSize sizeHint() const;
    void paintEvent(QPaintEvent *);

    qreal rangeStart() const;
    qreal rangeEnd() const;

    bool isReversed() const;
    void setReversed(bool r);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void rangeChanged(qreal start, qreal end);
    
public slots:
    void setRangeStart(qreal start);
    void setRangeEnd(qreal end);
    void setRange(qreal start, qreal end);
    void setTicks(int majors, int minors);
    
private:
    void drawGroove(QPainter *painter);
    void drawTicks(QPainter *painter);
    void drawIndicator(qreal rangeValue, QPainter *painter, QColor color = Qt::black);
    void drawCover(QPainter *painter);
    bool hitTest(const QPoint &pos, qreal rangeValue);
    int getPos(qreal rangeValue);
    qreal getValue(int pos);

    Qt::Orientation m_orient;
    qreal m_rangeMin, m_rangeMax;
    qreal m_rangeStart, m_rangeEnd;
    bool m_isDraggingStart;
    bool m_isDraggingEnd;
    qreal m_rangeCurrent;

    bool m_isReversed;

    int m_majorTicks;
    int m_minorTicks;
};
}
#endif // RANGEBAR_H
