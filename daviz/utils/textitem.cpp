#include "textitem.h"
#include <QPainter>
using namespace RadarDisplay;
TextItem::TextItem(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent),
    m_backgroundColor(Qt::black)
{
}

QColor TextItem::backgroundColor() const
{
    return m_backgroundColor;
}

void TextItem::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update();
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_backgroundColor);
    painter->drawRect(boundingRect());
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
