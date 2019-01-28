#include "coordsitem.h"
#include <QDebug>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QRect>
#include <QRectF>
#include <math.h>

using namespace RadarDisplay;

static const int SECTORS = 12;
static const int SECONDARY_SCALE_SIZE = 2;

CoordsItem::CoordsItem(Coords_Details primaryDetail,
                       Coords_Details secondaryDetail,
                       QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_distance(10000),
    m_primaryDetail(primaryDetail),
    m_secondaryDetail(secondaryDetail),
    m_radius(100)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

void CoordsItem::setDistance(qreal distance)
{
    m_distance = distance;
    update();
}

void CoordsItem::setRadius(qreal radius)
{
    if (radius > 0.0) {
        prepareGeometryChange();
        m_radius = radius;
    }
}

void CoordsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPen pen;
    pen.setWidth(1);
    pen.setCosmetic(true);

    qreal convUnit = m_radius/m_distance;

    // 绘制同心圆
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    for (int i = 0; i < primaryScales(); i++) {
        qreal primaryRadius = (i+1) * (int)m_primaryDetail * convUnit;
        painter->drawEllipse(QPointF(0.0, 0.0), primaryRadius, primaryRadius);
    }

    // 绘制扇区分割线与刻度
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    qreal maxRadius = primaryScales() * (int)m_primaryDetail * convUnit;
    for (int sector = 0; sector < SECTORS; sector++) {
        painter->drawLine(0.0, 0.0, maxRadius, 0);
        for (int i = 0; i < primaryScales(); i++) {
            qreal primaryRadius = (i+1) * (int)m_primaryDetail * convUnit;
            for (int j = 1; j < secondaryScales(); j++) {
                qreal secondaryRadius = primaryRadius - j * (int)m_secondaryDetail * convUnit;
                painter->drawLine(secondaryRadius, 0.0, secondaryRadius, SECONDARY_SCALE_SIZE);
            }
        }
        painter->rotate(360/SECTORS);
    }

    // 绘制刻度文字
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    for (int i = 0; i < primaryScales(); i++) {
        qreal primaryRadius = (i+1) * (int)m_primaryDetail * convUnit;
        int kilometers = (i+1) * (int)m_primaryDetail / 1000;
        painter->drawText(primaryRadius, 0, QString::number(kilometers));
        painter->drawText(0, -primaryRadius, QString::number(kilometers));
    }
}

QRectF CoordsItem::boundingRect() const
{
    QRectF rect(-m_radius, -m_radius, 2*m_radius, 2*m_radius);
    rect.adjust(-10, -10, 10, 10);
    return rect;
}

int CoordsItem::primaryScales() const
{
    return m_distance / (int)m_primaryDetail;
}

int CoordsItem::secondaryScales() const
{
    if (m_secondaryDetail >= m_primaryDetail)
        return 0;
    return (int)m_primaryDetail / (int)m_secondaryDetail;
}
