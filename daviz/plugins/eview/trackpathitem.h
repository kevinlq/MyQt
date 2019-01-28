#ifndef TRACKPATHITEM_H
#define TRACKPATHITEM_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPointF>
#include <QVector>

namespace RadarDisplay {
class TrackItem;
class TrackPathItem : public QGraphicsItem
{
public:
    TrackPathItem(QGraphicsItem *parentItem = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isEmpty() const;
    void addPoint(const QPointF &p);

private:
    void expandBoundingRect(const QPointF &p);
    void updateBoundingRect();
    void updateControlPoints();
    void updateSmoothPath();

    QVector<QPointF> m_points;
    QVector<QPointF> m_controlPoints;
    QVector<QPointF> m_midPoints;
    QRectF m_rect;
    QPainterPath m_smoothPath;
};
}

#endif // TRACKPATHITEM_H
