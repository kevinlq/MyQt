#ifndef COORDSITEM_H
#define COORDSITEM_H

#include <QGraphicsItem>
#include <QPointF>
#include <QSizeF>
#include <QRectF>

namespace RadarDisplay {
enum Coords_Details {
    Coords_OneDegree = 1,
    Coords_FiveDegrees = 5,
    Coords_TenDegrees = 10
};

class CoordsItem : public QGraphicsItem
{
public:
    CoordsItem(Coords_Details primaryDetail,
               Coords_Details secondaryDetail,
               QGraphicsItem *parent = 0);
    void setRadius(qreal radius);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int primaryScales() const;
    int secondaryScales() const;
    Coords_Details m_primaryDetail;
    Coords_Details m_secondaryDetail;
    qreal m_radius;
};

}

#endif // COORDSITEM_H
