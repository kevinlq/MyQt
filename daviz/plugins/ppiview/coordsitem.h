#ifndef COORDSITEM_H
#define COORDSITEM_H

#include <QGraphicsItem>
#include <QPointF>
#include <QSizeF>
#include <QRectF>

namespace RadarDisplay {
enum Coords_Details {
    Coords_OneKilometer = 1000,
    Coords_FiveKilometers = 5000,
    Coords_TenKilometers = 10000
};

class CoordsItem : public QGraphicsItem
{
public:
    CoordsItem(Coords_Details primaryDetail,
               Coords_Details secondaryDetail,
               QGraphicsItem *parent = 0);
    void setDistance(qreal distance);
    void setRadius(qreal radius);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int primaryScales() const;
    int secondaryScales() const;
    qreal m_distance;
    Coords_Details m_primaryDetail;
    Coords_Details m_secondaryDetail;
    qreal m_radius;
};

}

#endif // COORDSITEM_H
