#include "selectionitem.h"
#include <QPen>
#include <QBrush>
#include <QPainterPath>
using namespace RadarDisplay;

SelectionItem::SelectionItem(QGraphicsItem *parent) :
    QGraphicsPathItem(parent)
{
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 120));
    pen.setStyle(Qt::SolidLine);
    setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 180, 120));
    setBrush(brush);

    setPath(QPainterPath());
    setCacheMode(QGraphicsItem::NoCache);
}
