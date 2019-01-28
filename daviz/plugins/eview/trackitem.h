#ifndef TRACKITEM_H
#define TRACKITEM_H

#include "core/icore.h"

#include <QGraphicsItem>
#include <QMap>
#include <QObject>
#include <QPointF>

namespace RadarDisplay {
class ITarget;
class ITrack;
class TargetItem;
class PPIView;
class TrackPathItem;
class TrackItem : public QGraphicsItem
{
public:
    TrackItem(const TrackData &track, QGraphicsItem *parent = 0);
    ~TrackItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void addPoint(const QPointF &p);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    TrackData m_track;
    QPointF m_lastPos;
    QList<TargetItem *> m_targets;
    TrackPathItem *m_path;
};
}
#endif // TRACKITEM_H
