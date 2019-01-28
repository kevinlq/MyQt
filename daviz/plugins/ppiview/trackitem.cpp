#include "trackitem.h"
#include "trackpathitem.h"
#include <QDebug>
#include <QRectF>
#include <QPointF>
#include <QPainter>
#include <QPen>
#include <QGraphicsScene>

using namespace RadarDisplay;

TrackItem::TrackItem(const TrackData &track, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_track(track),
    m_path(new TrackPathItem)
{
    setFlags(QGraphicsItem::ItemIgnoresTransformations);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

TrackItem::~TrackItem()
{
    delete m_path;
}

void TrackItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPen pen;
    pen.setCosmetic(true);
    pen.setBrush(Qt::red);
    painter->setPen(pen);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(m_track.id));
}

QRectF TrackItem::boundingRect() const
{
    return QRectF(-20, -10, 40, 20);
}

void TrackItem::addPoint(const QPointF &p)
{
    m_path->addPoint(p);
    setPos(p);
}

QVariant TrackItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSceneHasChanged) {
        if (scene())
            scene()->addItem(m_path);
        else {
            if (m_path->scene())
                m_path->scene()->removeItem(m_path);
        }
        return QVariant();
    } else if (change == QGraphicsItem::ItemVisibleHasChanged) {
        m_path->setVisible(isVisible());
        return QVariant();
    }
    return QGraphicsItem::itemChange(change, value);
}
