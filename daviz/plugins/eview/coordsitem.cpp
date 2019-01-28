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

namespace {
static const int SECTORS = 12;
static const int SECONDARY_SCALE_SIZE = 2;
}

CoordsItem::CoordsItem(Coords_Details primaryDetail,
                       Coords_Details secondaryDetail,
                       QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_primaryDetail(primaryDetail),
    m_secondaryDetail(secondaryDetail),
    m_radius(100)
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
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

    // 绘制网格扇区分割线与刻度
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    for (int sector = 0; sector <= SECTORS; sector++) {
        qreal x = sector * 2 * m_radius / SECTORS - m_radius;
        painter->drawLine(x, -m_radius, x, m_radius);
    }

    for (int i = 0; i <= primaryScales(); i++) {
        qreal y = m_radius - i * (int)m_primaryDetail * (2 * m_radius) / 90;
        painter->drawLine(-m_radius, y, m_radius, y);
        for (int j = 1; j < secondaryScales(); j++) {
            y += (int)m_secondaryDetail * (2 * m_radius) / 90;
            painter->drawLine(-m_radius, y, -m_radius + 2, y);
        }
    }

    // 绘制刻度文字
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    for (int sector = 1; sector < SECTORS; sector++) {
        qreal x = sector * 2 * m_radius / SECTORS - m_radius;
        int degree = sector * 360 / SECTORS;
        painter->drawText(x, m_radius, QString::number(degree));
    }
    for (int i = 0; i <= primaryScales(); i++) {
        qreal y = m_radius - i * (int)m_primaryDetail * (2 * m_radius) / 90;
        int degrees = i * (int)m_primaryDetail;
        painter->drawText(-m_radius, y, QString::number(degrees));
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
    return 90 / (int)m_primaryDetail;
}

int CoordsItem::secondaryScales() const
{
    if (m_secondaryDetail >= m_primaryDetail)
        return 0;
    return (int)m_primaryDetail / (int)m_secondaryDetail;
}
