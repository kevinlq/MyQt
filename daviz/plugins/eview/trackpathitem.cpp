#include "trackpathitem.h"
#include "trackitem.h"
#include <QPainter>
#include <QDebug>

namespace RadarDisplay {

TrackPathItem::TrackPathItem(QGraphicsItem *parentItem) :
    QGraphicsItem(parentItem)
{
    setZValue(-0.5);
//    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

QRectF TrackPathItem::boundingRect() const
{
    return m_rect;
}

void TrackPathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setCosmetic(true);

    // 画折线
    /*
    pen.setColor(Qt::yellow);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawPolyline(m_points.data(), m_points.size());
    */

    /*
    // 画控制点及其连线
    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawLines(m_controlPoints.data(), m_controlPoints.size() / 2);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawPoints(m_controlPoints.data(), m_controlPoints.size());
    */

    // 画平滑后的
    pen.setColor(Qt::yellow);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawPath(m_smoothPath);

    // 画点
    pen.setColor(Qt::yellow);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawPoints(m_points.data(), m_points.size());
}

bool TrackPathItem::isEmpty() const
{
    return m_points.isEmpty();
}

void TrackPathItem::addPoint(const QPointF &p)
{
    m_points << p;
    updateControlPoints();
    updateBoundingRect();
    updateSmoothPath();
    prepareGeometryChange();
    update();
}

void TrackPathItem::expandBoundingRect(const QPointF &p)
{
    if (p.x() < m_rect.left())
        m_rect.setLeft(p.x());
    if (p.x() > m_rect.right())
        m_rect.setRight(p.x());
    if (p.y() < m_rect.top())
        m_rect.setTop(p.y());
    if (p.y() > m_rect.bottom())
        m_rect.setBottom(p.y());
}

void TrackPathItem::updateBoundingRect()
{
    foreach (const QPointF &p, m_points)
        expandBoundingRect(p);
    foreach (const QPointF &p, m_controlPoints)
        expandBoundingRect(p);
}

void TrackPathItem::updateControlPoints()
{
    int pointCount = m_points.size();
    if (pointCount <= 1)
        return;
    QPointF midPoint = (m_points[pointCount - 2] + m_points[pointCount - 1]) / 2;
    m_midPoints << midPoint;

    if (pointCount == 2)
        return;

    int midPointCount = m_midPoints.size();
    QPointF midMidPoint = (m_midPoints[midPointCount - 2] + m_midPoints[midPointCount - 1]) / 2;
    qreal scale = 0.6;
    QPointF scaledStartPoint = (m_midPoints[midPointCount - 2] - midMidPoint) * scale + midMidPoint;
    QPointF scaledEndPoint = (m_midPoints[midPointCount - 1] - midMidPoint) * scale + midMidPoint;
    QPointF moveToPoint = m_points[midPointCount - 1];
    QPointF deltaDist = moveToPoint - midMidPoint;
    m_controlPoints << (scaledStartPoint + deltaDist);
    m_controlPoints << (scaledEndPoint + deltaDist);

}

void TrackPathItem::updateSmoothPath()
{
    int pointCount = m_points.size();
    if (pointCount == 0)
        return;
    QPointF p = m_points.last();
    if (pointCount == 1) {
        m_smoothPath.moveTo(p);
        return;
    }
    if (pointCount == 2) {
        m_smoothPath.lineTo(p);
        return;

    }
    m_smoothPath = QPainterPath(m_points[0]);
    m_smoothPath.quadTo(m_controlPoints[0], m_points[1]);
    for (int i = 1; i < pointCount - 2; i++) {
        m_smoothPath.cubicTo(m_controlPoints[2 * i - 1], m_controlPoints[2 * i], m_points[i + 1]);
    }
    m_smoothPath.quadTo(m_controlPoints.last(), m_points.last());
}

}
